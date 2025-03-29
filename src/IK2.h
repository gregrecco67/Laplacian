#include "raylib.h"
#include <stdlib.h>
#include <math.h>

void ImageKernelNoAlpha(Image *image, const float *kernel, int kernelSize)
{
    if ((image->data == NULL) || (image->width == 0) || (image->height == 0) || kernel == NULL) return;

    int kernelWidth = (int)sqrtf((float)kernelSize);

    if (kernelWidth*kernelWidth != kernelSize)
    {
        //TRACELOG(LOG_WARNING, "IMAGE: Convolution kernel must be square to be applied");
        return;
    }

    Color *pixels = LoadImageColors(*image);

    Vector4 *imageCopy2 = (Vector4*)malloc((image->height)*(image->width)*sizeof(Vector4));
    Vector4 *temp = (Vector4*)malloc(kernelSize*sizeof(Vector4));

    for (int i = 0; i < kernelSize; i++)
    {
        temp[i].x = 0.0f;
        temp[i].y = 0.0f;
        temp[i].z = 0.0f;
        temp[i].w = 0.0f;
    }

    float rRes = 0.0f;
    float gRes = 0.0f;
    float bRes = 0.0f;
    float aRes = 0.0f;

    int startRange = 0, endRange = 0;

    if (kernelWidth%2 == 0)
    {
        startRange = -kernelWidth/2;
        endRange = kernelWidth/2;
    }
    else
    {
        startRange = -kernelWidth/2;
        endRange = kernelWidth/2 + 1;
    }

    for (int x = 0; x < image->height; x++)
    {
        for (int y = 0; y < image->width; y++)
        {
            for (int xk = startRange; xk < endRange; xk++)
            {
                for (int yk = startRange; yk < endRange; yk++)
                {
                    int xkabs = xk + kernelWidth/2;
                    int ykabs = yk + kernelWidth/2;
                    unsigned int imgindex = image->width*(x + xk) + (y + yk);

                    if (imgindex >= (unsigned int)(image->width*image->height))
                    {
                        temp[kernelWidth*xkabs + ykabs].x = 0.0f;
                        temp[kernelWidth*xkabs + ykabs].y = 0.0f;
                        temp[kernelWidth*xkabs + ykabs].z = 0.0f;
                        temp[kernelWidth*xkabs + ykabs].w = 0.0f;
                    }
                    else
                    {
                        temp[kernelWidth*xkabs + ykabs].x = ((float)pixels[imgindex].r)/255.0f*kernel[kernelWidth*xkabs + ykabs];
                        temp[kernelWidth*xkabs + ykabs].y = ((float)pixels[imgindex].g)/255.0f*kernel[kernelWidth*xkabs + ykabs];
                        temp[kernelWidth*xkabs + ykabs].z = ((float)pixels[imgindex].b)/255.0f*kernel[kernelWidth*xkabs + ykabs];
                        temp[kernelWidth*xkabs + ykabs].w = ((float)pixels[imgindex].a)/255.0f*kernel[kernelWidth*xkabs + ykabs];
                    }
                }
            }

            for (int i = 0; i < kernelSize; i++)
            {
                rRes += temp[i].x;
                gRes += temp[i].y;
                bRes += temp[i].z;
                aRes += temp[i].w;
            }

            if (rRes < 0.0f) rRes = 0.0f;
            if (gRes < 0.0f) gRes = 0.0f;
            if (bRes < 0.0f) bRes = 0.0f;

            if (rRes > 1.0f) rRes = 1.0f;
            if (gRes > 1.0f) gRes = 1.0f;
            if (bRes > 1.0f) bRes = 1.0f;

            imageCopy2[image->width*x + y].x = rRes;
            imageCopy2[image->width*x + y].y = gRes;
            imageCopy2[image->width*x + y].z = bRes;
            imageCopy2[image->width*x + y].w = aRes;

            rRes = 0.0f;
            gRes = 0.0f;
            bRes = 0.0f;
            aRes = 0.0f;

            for (int i = 0; i < kernelSize; i++)
            {
                temp[i].x = 0.0f;
                temp[i].y = 0.0f;
                temp[i].z = 0.0f;
                temp[i].w = 0.0f;
            }
        }
    }

    for (int i = 0; i < (image->width*image->height); i++)
    {
        // float alpha = 1.0f; //(float)imageCopy2[i].w;

        pixels[i].r = (unsigned char)((imageCopy2[i].x)*255.0f);
        pixels[i].g = (unsigned char)((imageCopy2[i].y)*255.0f);
        pixels[i].b = (unsigned char)((imageCopy2[i].z)*255.0f);
        pixels[i].a = (unsigned char)(/*(alpha)**/255.0f);
    }

    int format = image->format;
    RL_FREE(image->data);
    RL_FREE(imageCopy2);
    RL_FREE(temp);

    image->data = pixels;
    image->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    ImageFormat(image, format);
}