using NUnit.Framework;

namespace Fugro.OpenCV.Test
{
    [TestFixture]
    internal sealed class DoubleArrayTests
    {
        [Test]
        public void TestAdd()
        {
            var first = new DoubleArray(new[] { 1.0, 2.0, 3.0, 4.0 }, 2, 2);

            var result = first.Add(first);

            Assert.AreEqual(2.0, result.At(0, 0), 1e-12);
            Assert.AreEqual(4.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(6.0, result.At(0, 1), 1e-12);
            Assert.AreEqual(8.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestSubstract()
        {
            var first = new DoubleArray(new[] { 3.0 }, 1, 1);
            var second = new DoubleArray(new[] { 2.0 }, 1, 1);

            var result = first.Substract(second);

            Assert.AreEqual(1.0, result.At(0, 0), 1e-12);
        }

        [Test]
        public void TestMultiply()
        {
            var data = new DoubleArray(new[] { 1.0, 2.0, 3.0, 4.0 }, 2, 2);

            var result = data.Multiply(data);

            Assert.AreEqual(1.0, result.At(0, 0), 1e-12);
            Assert.AreEqual(4.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(9.0, result.At(0, 1), 1e-12);
            Assert.AreEqual(16.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestMultiplyScalar()
        {
            var data = new DoubleArray(new[] { 1.0, 2.0, 3.0, 4.0 }, 2, 2);

            var result = data.Multiply(2.0);

            Assert.AreEqual(2.0, result.At(0, 0), 1e-12);
            Assert.AreEqual(4.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(6.0, result.At(0, 1), 1e-12);
            Assert.AreEqual(8.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestMaximumLocation()
        {
            var data = new DoubleArray(new[] { 1.0, 2.0, 5.0, 4.0 }, 2, 2);

            var max = data.MaxLoc();

            Assert.AreEqual(5.0, data.At(max), 1e-12);
        }

        [Test]
        public void TestDivide()
        {
            var data = new DoubleArray(new[] { 1.0, 2.0, 3.0, 4.0 }, 2, 2);

            var result = data.Divide(data);

            Assert.AreEqual(1.0, result.At(0, 0), 1e-12);
            Assert.AreEqual(1.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(1.0, result.At(0, 1), 1e-12);
            Assert.AreEqual(1.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestDivideScalar()
        {
            var data = new DoubleArray(new[] { 1.0, 2.0, 3.0, 4.0 }, 2, 2);

            var result = data.Divide(2.0);

            Assert.AreEqual(0.5, result.At(0, 0), 1e-12);
            Assert.AreEqual(1.0, result.At(1, 0), 1e-12);
            Assert.AreEqual(1.5, result.At(0, 1), 1e-12);
            Assert.AreEqual(2.0, result.At(1, 1), 1e-12);
        }

        [Test]
        public void TestDiscreteFourierTransformation()
        {
            var input = new DoubleArray(new[] { 1.0, 2.0 }, 1, 2);
            var result = input.Dft(DftTransformations.ComplexOutput);

            Assert.IsNotNull(result);
        }

        [Test]
        public void TestChannelMergeSplit()
        {
            var channel1 = new DoubleArray(new[] { 1.0, 2.0 }, 1, 2);
            var channel2 = new DoubleArray(new[] { 1.0, 2.0 }, 1, 2);
            var channel3 = new DoubleArray(new[] { 1.0, 2.0 }, 1, 2);

            Assert.AreEqual(1, channel1.ChannelCount);
            Assert.AreEqual(1, channel2.ChannelCount);
            Assert.AreEqual(1, channel3.ChannelCount);

            var result = channel1.Merge(channel2, channel3);
            channel1.Dispose();
            channel2.Dispose();
            channel3.Dispose();

            Assert.AreEqual(3, result.ChannelCount);

            var channels = result.Split();
            Assert.AreEqual(3, channels.Length);

            Assert.AreEqual(1.0, channels[0].At(0, 0), 1e-12);
            Assert.AreEqual(2.0, channels[0].At(0, 1), 1e-12);
            Assert.AreEqual(1.0, channels[1].At(0, 0), 1e-12);
            Assert.AreEqual(2.0, channels[1].At(0, 1), 1e-12);
            Assert.AreEqual(1.0, channels[2].At(0, 0), 1e-12);
            Assert.AreEqual(2.0, channels[2].At(0, 1), 1e-12);
        }

       [Test]
        public void TestInverseDiscreteFourierTransformation()
        {
            var input = new DoubleArray(new[] { 1.0, 2.0 }, 1, 2);
            var result = input.InverseDft(DftTransformations.ComplexOutput);

            Assert.NotNull(result);
        }

        [Test]
        public void TestOptimalDftSize()
        {
            var optimalSize = Dft.GetOptimalSize(98);

            Assert.AreEqual(100, optimalSize);
        }

        [Test]
        public void TestIntegralImage()
        {
            var input = new DoubleArray(new[] { 10000.0, 20000.0, 30000.0, 40000.0 }, 2, 2);
            var result = input.Integral();

            //In accessing DoubleArray, first comes colomn and then rows. result.At(col,row)
            Assert.AreEqual(10000.0, result.At(1, 1), 1e-12);
            Assert.AreEqual(30000.0, result.At(2, 1), 1e-12);
            Assert.AreEqual(40000.0, result.At(1, 2), 1e-12);
            Assert.AreEqual(100000.0, result.At(2, 2), 1e-12);
        }
    }
}
