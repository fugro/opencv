using System;
using System.Linq;
using System.Windows;
using NUnit.Framework;

namespace Fugro.OpenCV.Test
{
    [TestFixture]
    internal sealed class ImageArrayTests
    {
        [Test]
        public void TestResize()
        {
            const int width = 9;
            const int height = 6;

            var image = new ImageArray(Enumerable.Range(0, width * height).Select(i => (byte)i).ToArray(), width, height);

            const int newWidth = 3;
            const int newHeight = 2;

            var resizedImage = image.Resize(newWidth, newHeight);

            Assert.AreEqual(newWidth, resizedImage.Columns);
            Assert.AreEqual(newHeight, resizedImage.Rows);

            var expectedBytes = Resize(image, newWidth, newHeight);

            Assert.IsTrue(expectedBytes.SequenceEqual(resizedImage.CopyPixels()));
        }

        private byte[] Resize(ImageArray someImage, int newWidth, int newHeight)
        {
            byte[] newBytes = new byte[newWidth * newHeight];

            for (int column = 0; column < newWidth; column++)
            {
                for (int row = 0; row < newHeight; row++)
                {
                    var originalX = Math.Floor((someImage.Columns / (double)newWidth) * column);
                    var originalY = Math.Floor((someImage.Rows / (double)newHeight) * row);
                    newBytes[row * newWidth + column] = someImage.At((int)originalX, (int)originalY);
                }
            }

            return newBytes;
        }

        [Test]
        public void TestRoi()
        {
            var image = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);

            var roi = image.ExtractRoi(new Int32Rect(1, 1, 1, 1));

            Assert.AreEqual(4, roi.At(0, 0));
        }

        [Test]
        public void TestRoiOutsideRange()
        {
            var image = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);

            var largeRoi = image.ExtractRoi(new Int32Rect(-2, -2, 4, 4));

            Assert.AreEqual(4, largeRoi.At(1, 1));
        }

        [Test]
        public void TestSetTo()
        {
            var image = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);

            var roi = image.ExtractRoi(new Int32Rect(0, 1, 2, 1));
            roi.SetTo(0);

            Assert.AreEqual(0, image.At(0, 1));
            Assert.AreEqual(0, image.At(1, 1));
        }

        [Test]
        public void TestGetPixels()
        {
            var blue = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);
            var green = new ImageArray(new byte[] { 5, 6, 7, 8 }, 2, 2);
            var red = new ImageArray(new byte[] { 11, 12, 13, 14 }, 2, 2);

            var image = blue.Merge(green, red);

            var pixels = image.CopyPixels();

            Assert.AreEqual(12, pixels.Length);
            Assert.AreEqual(blue.At(0, 0), pixels[0]);
            Assert.AreEqual(green.At(0, 0), pixels[1]);
            Assert.AreEqual(red.At(0, 0), pixels[2]);
        }

        [Test]
        public void TestGetSubPixelValue()
        {
            var image = new ImageArray(new byte[] { 1, 1, 3, 3 }, 2, 2);

            var value = image.GetSubPixelValue(0.5, 0.5);

            Assert.AreEqual(2, value);
        }

        [Test]
        public void TestThreshold()
        {
            var image = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);

            var result = image.Threshold(2, 10, ThresholdType.Binary);

            Assert.AreEqual(0, result.At(0, 0));
            Assert.AreEqual(0, result.At(1, 0));
            Assert.AreEqual(10, result.At(0, 1));
            Assert.AreEqual(10, result.At(1, 1));
        }

        [Test]
        public void TestDoubleConversion()
        {
            var image = new ImageArray(new byte[] { 1, 2, 3, 4 }, 2, 2);

            var result = image.ToDoubleArray();

            Assert.AreEqual(1.0, result.At(0, 0), 1e-12);
            Assert.AreEqual(2.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(3.0, result.At(0, 1), 1e-12);
            Assert.AreEqual(4.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestCornerSubPixel()
        {
            ImageArray image = CreateSaddlePointImage(10);

            var corners = new[] { new DoublePoint(9.3, 9.7) };

            var subPixel = image.CornerSubPixel(corners, new Int32Size(3, 3), 10, 0.03).Single();

            Assert.AreEqual(9.5, subPixel.X, 0.01);
            Assert.AreEqual(9.5, subPixel.Y, 0.01);
        }

        [Test]
        public void TestCornerSubPixelInitialPointTwo()
        {
            ImageArray image = CreateSaddlePointImage(50);

            var corners = new[] { new DoublePoint(46.8, 54.7) };

            var subPixel = image.CornerSubPixel(corners, new Int32Size(6, 6), 10, 0.05).Single();

            Assert.AreEqual(49.5, subPixel.X, 0.01);
            Assert.AreEqual(49.5, subPixel.Y, 0.01);
        }

        [Test]
        public void TestImageMean()
        {
            var byteImage = new byte[2 * 2];
            byteImage[0] = 100;
            byteImage[1] = 100;
            byteImage[2] = 0;
            byteImage[3] = 0;
            ImageArray imageA = new ImageArray(byteImage, 2, 2);
            var mean = imageA.Mean();

            Assert.AreEqual(50, mean);
        }

        [Test]
        public void TestMatchTemplate()
        {
            ImageArray image = SimulateBlackImageWithWhitePatch(41, 41, new Int32Rect(12, 23, 10, 10));
            ImageArray template = SimulateBlackImageWithWhitePatch(21, 21, new Int32Rect(10, 10, 10, 10));
            DoubleArray match = image.MatchTemplate(template, TemplateMatchingMethod.SquaredDifference);

            var minLoc = match.MinLoc();
            Assert.AreEqual(minLoc.X, 2, 1e-3);
            Assert.AreEqual(minLoc.Y, 13, 1e-3);
        }

        [Test]
        public void TestCalculateOpticalFlow()
        {
            ImageArray imageA = SimulateBlackImageWithWhitePatch(41, 41, new Int32Rect(12, 23, 10, 10));
            ImageArray imageB = SimulateBlackImageWithWhitePatch(41, 41, new Int32Rect(14, 25, 10, 10));

            var inputPoints = new[] { new DoublePoint(12.0, 23.0) };

            var matchedPoint = imageA.CalculateOpticalFlowPyrLK(imageB, inputPoints, new Int32Size(5, 5), 0).Single();

            Assert.AreEqual(14, matchedPoint.TrackedPoint.X, 1e-3);
            Assert.AreEqual(25, matchedPoint.TrackedPoint.Y, 1e-3);
        }

        [Test]
        public void TestGoodFeaturesToTrack()
        {
            ImageArray image = CreateSaddlePointImage(10);

            var corners = image.GoodFeaturesToTrack(1, 0.1, 2).ToList();

            var subPixel = image.CornerSubPixel(corners, new Int32Size(3, 3), 10, 0.03).Single();

            Assert.AreEqual(1, corners.Count);
            Assert.AreEqual(9.5, subPixel.X, 0.01);
            Assert.AreEqual(9.5, subPixel.Y, 0.01);
        }

        [Test]
        public void TestGoodFeaturesToTrackWithMask()
        {
            ImageArray image = CreateSaddlePointImage(10);
            var corners = image.GoodFeaturesToTrack(1, 0.1, 2).ToList();

            Assert.AreEqual(1, corners.Count);

            var cornersInRoi = image.GoodFeaturesToTrack(1, 0.1, 2, new Int32Rect(0, 0, 3, 3));

            Assert.AreEqual(0, cornersInRoi.Count());
        }

        [Test]
        public void TestSeparableFilter2D()
        {
            var gaussiankernel1D = Kernel.GetGaussianKernel(7, 2.0);

            var image = BuildRandomImage(50, 50);

            var expectedResult = image.GaussianBlur(7, 7, 2.0, 2.0);

            var result = image.Filter2DSeparable(gaussiankernel1D, gaussiankernel1D);

            var expectedPixels = expectedResult.CopyPixels();
            var resultPixels = result.CopyPixels();

            for (int i = 0; i < expectedPixels.Length; i++)
            {
                Assert.AreEqual(expectedPixels[i], resultPixels[i], 1e-8);
            }
        }

        [Test]
        public void TestGrayscaleConversion()
        {
            var blue = BuildRandomImage(50, 50);
            var green = BuildRandomImage(50, 50);
            var red = BuildRandomImage(50, 50);

            var bgr = blue.Merge(green, red);
            Assert.AreEqual(3, bgr.ChannelCount);

            var gray = bgr.ConvertColor(ColorConversion.BGR2GRAY);
            Assert.AreEqual(1, gray.ChannelCount);
        }

        [Test]
        public void TestColorConversion()
        {
            var image = BuildRandomImage(50, 50);

            var bgr = image.ConvertColor(ColorConversion.GRAY2BGR);
            Assert.AreEqual(3, bgr.ChannelCount);

            var gray = bgr.ConvertColor(ColorConversion.BGR2GRAY);
            Assert.AreEqual(1, gray.ChannelCount);
        }

        [Test]
        public void TestRedImageToHsvConversion()
        {
            var redImage = BuildRedImage();

            var hsvImage = redImage.ConvertColor(ColorConversion.BGR2HSV).Split();

            Assert.AreEqual(0, hsvImage[0].At(0, 0));
            Assert.AreEqual(255, hsvImage[1].At(0, 0));
            Assert.AreEqual(255, hsvImage[2].At(0, 0));
        }

        [Test]
        public void TestBayerConversion()
        {
            var bayer = BuildRandomImage(50, 50);

            var image = bayer.ConvertColor(ColorConversion.BayerBG2BGR);

            Assert.AreEqual(3, image.ChannelCount);
        }

        private ImageArray BuildRandomImage(int imageWidth, int imageHeight)
        {
            var pixels = new byte[imageWidth * imageHeight];
            var random = new Random();
            random.NextBytes(pixels);

            return new ImageArray(pixels, imageWidth, imageHeight);
        }

        private static ImageArray BuildRedImage()
        {
            var blue = new ImageArray(new byte[250], 50, 50);
            var green = new ImageArray(new byte[250], 50, 50);

            var red = new ImageArray(Enumerable.Repeat((byte)255, 250).ToArray(), 50, 50);

            return blue.Merge(green, red);
        }

        private ImageArray SimulateBlackImageWithWhitePatch(int imageWidth, int imageHeight, Int32Rect roi)
        {
            var byteImage = new byte[imageWidth * imageHeight];

            for (int x = roi.X; x < roi.X + roi.Width; x++)
            {
                for (int y = roi.Y; y < roi.Y + roi.Height; y++)
                {
                    var index = x + y * imageWidth;
                    byteImage[index] = 255;
                }
            }

            return new ImageArray(byteImage, imageWidth, imageHeight);
        }

        private static ImageArray CreateSaddlePointImage(int corner)
        {
            var width = corner * 2;
            var height = corner * 2;

            return CreateSaddlePointImage(corner, width, height);
        }

        private static ImageArray CreateSaddlePointImage(int corner, int width, int height)
        {
            var byteImage = new byte[width * height];

            Action<int, int> setPixel = (x, y) => byteImage[x + y * width] = 255;

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    if (x > corner - 1 && y < corner)
                    {
                        setPixel(x, y);
                    }
                    else if (y > corner - 1 && x < corner)
                    {
                        setPixel(x, y);
                    }
                }
            }

            return new ImageArray(byteImage, width, height);
        }
    }
}
