# Disclaimer
This repository is no longer maintained and it has been archived.

----------------------------------------

# opencv
A .Net wrapper for the OpenCV (Open Source Computer Vision) library

## Get Started
Clone this project and build it by using Visual Studio 2017. Reference Fugro.OpenCV.dll in your own project and you are ready to go. The repository includes unit tests which can be run by using NUnit.

### C# example

In the following example, we create a sobel image from Lena and save it to a file.

```c#
ImageArray image = new ImageArray("lena.png");
DoubleArray sobelArray = image.Sobel(2, 2, 5);
sobelArray.ToImageArray().Save("sobel_lena.png");
```

## Externals
For easy compilation, we included necessary parts of [OpenCV](https://github.com/opencv/opencv).

## License
This library is licensed under the MIT License
