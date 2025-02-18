#include "ada/gl/gl.h"

#if defined(PLATFORM_RPI)

namespace ada {

    #ifndef DRIVER_BROADCOM
    static PFNEGLCREATEIMAGEKHRPROC createImageProc = NULL;
    static PFNEGLDESTROYIMAGEKHRPROC destroyImageProc = NULL;
    static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC imageTargetTexture2DProc = NULL;
    #endif

    EGLImageKHR createImage(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list) {

        #ifdef DRIVER_BROADCOM
        return eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);

        #else
        if (!createImageProc)
            createImageProc = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress("eglCreateImageKHR");

        return createImageProc(dpy, ctx, target, buffer, attrib_list);
        #endif
    }

    EGLBoolean destroyImage(EGLDisplay dpy, EGLImageKHR image) {

        #ifdef DRIVER_BROADCOM
        return eglDestroyImageKHR(dpy, image);

        #else
        if (!destroyImageProc)
            destroyImageProc = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress("eglDestroyImageKHR");
        
        return destroyImageProc(dpy, image);
        #endif
    }

    void imageTargetTexture2D(EGLenum target, EGLImageKHR image) {

        #ifdef DRIVER_BROADCOM
        return glEGLImageTargetTexture2DOES(target, image);

        #else
        if (!imageTargetTexture2DProc)
            imageTargetTexture2DProc = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) eglGetProcAddress("glEGLImageTargetTexture2DOES");
        
        imageTargetTexture2DProc(target, image);
        #endif
    }
}

#endif