using System;
using System.Linq;
using System.Windows;
using NUnit.Framework;

namespace Fugro.OpenCV.Test
{
    [TestFixture]
    internal sealed class ContourTests
    {
        [Test]
        public void TestFitEllipse()
        {
            var circlePoints = Enumerable.Range(0, 50).Select(i => i / 50.0 * Math.PI * 2).Select(a => new Point(Math.Cos(a), Math.Sin(a)));
            var ellipseCenter = new Point(500, 502);
            const double minorRadius = 20.0;
            const double majorRadius = 41.0;
            const double phiInRadians = 10.0 * Math.PI / 180;

            var ellipse = circlePoints.Select(p => new Point(p.X * majorRadius, p.Y * minorRadius))
                                      .Select(p => new Point(Math.Cos(phiInRadians) * p.X - Math.Sin(phiInRadians) * p.Y, Math.Sin(phiInRadians) * p.X + Math.Cos(phiInRadians) * p.Y))
                                      .Select(p => new DoublePoint(p.X + ellipseCenter.X, p.Y + ellipseCenter.Y));

            var ellipseInfo = new Contour(ellipse.ToArray()).FitEllipse();

            Assert.AreEqual(ellipseCenter.X, ellipseInfo.Center.X, 1.0e-5);
            Assert.AreEqual(ellipseCenter.Y, ellipseInfo.Center.Y, 1.0e-5);
            Assert.AreEqual(minorRadius, ellipseInfo.MinorRadius, 1.0e-5);
            Assert.AreEqual(majorRadius, ellipseInfo.MajorRadius, 1.0e-5);
            Assert.AreEqual(phiInRadians, WrapAngle(ellipseInfo.OrientationInDegrees - 90.0) * Math.PI / 180, 1.0e-5);
        }

        [Test]
        public void TestFitSmallEllipse()
        {
            var circlePoints = Enumerable.Range(0, 50).Select(i => i / 50.0 * Math.PI * 2).Select(a => new Point(Math.Cos(a), Math.Sin(a)));
            var ellipseCenter = new Point(0.0, 0.0);
            const double minorRadius = 0.001;
            const double majorRadius = 0.003;
            const double phiInRadians = 95.1 * Math.PI / 180;

            var ellipse = circlePoints.Select(p => new Point(p.X * majorRadius, p.Y * minorRadius))
                                      .Select(p => new Point(Math.Cos(phiInRadians) * p.X - Math.Sin(phiInRadians) * p.Y, Math.Sin(phiInRadians) * p.X + Math.Cos(phiInRadians) * p.Y))
                                      .Select(p => new Point(p.X + ellipseCenter.X, p.Y + ellipseCenter.Y));

            var scaledContour = ellipse.Select(p => new DoublePoint(p.X, p.Y));

            var ellipseInfo = new Contour(scaledContour.ToArray()).FitEllipse();

            Assert.AreEqual(ellipseCenter.X, ellipseInfo.Center.X, 1.0e-5);
            Assert.AreEqual(ellipseCenter.Y, ellipseInfo.Center.Y, 1.0e-5);
            Assert.AreEqual(minorRadius, ellipseInfo.MinorRadius, 1.0e-5);
            Assert.AreEqual(majorRadius, ellipseInfo.MajorRadius, 1.0e-5);
            Assert.AreEqual(phiInRadians, WrapAngle(ellipseInfo.OrientationInDegrees - 90.0) * Math.PI / 180, 1.0e-5);
        }

        private double WrapAngle(double degrees)
        {
            return (180.0 + degrees) % 180;
        }
    }
}
