using System;
using System.Linq;
using NUnit.Framework;

namespace Fugro.OpenCV.Test
{
    [TestFixture]
    internal sealed class KernelTests
    {
        [Test]
        public void TestGetGaussianKernel()
        {
            const double sigma = 1.0;
            const int size = 7;

            var gaussianKernel = Kernel.GetGaussianKernel(size, sigma);

            var gauss = Enumerable.Range(-size / 2, size).Select(i => Math.Exp(-i * i / (2 * sigma * sigma))).ToList();
            var sum = gauss.Sum();

            for (int i = 0; i < size; i++)
            {
                var expected = gauss[i] / sum;
                Assert.AreEqual(expected, gaussianKernel.At(0, i), 1e-8);
            }
        }
    }

}
