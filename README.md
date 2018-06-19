QRender by A.B. Sørensen

A student project - if you have any questions or I'm using something which I'm not allowed to or need to put in credit to something, please don't hesitate to contant med at s125010 ( at ) student.dtu.dk.
A base real-time renderer will be implemented and then I will go on to implement more features.
It will be implemented with Visual Studio 2017, OpenGL 3.3, C++ and an NVidia GTX970 GPU.

Dependencies:



Base implementation will be based on:

https://learnopengl.com/

with ImGui as the GUI library:

https://github.com/ocornut/imgui

and with RenderDoc for graphics debugger:

https://renderdoc.org/

and with stb_image for image loading:

https://github.com/nothings/stb/blob/master/stb_image.h



A wishlist for later:


Lens Flare:
http://john-chapman-graphics.blogspot.com/2013/02/pseudo-lens-flare.html
https://mynameismjp.wordpress.com/2009/12/15/more-post-processing-tricks-lens-flare/
http://resources.mpi-inf.mpg.de/lensflareRendering/pdf/flare.pdf


Camera Models and Physically Based Rendering:
https://www.slideshare.net/siliconstudio/subtle-anamorphic-lens-effects-realtime-rendering-of-physically-based-optical-effect-in-theory-and-practice-siggraph-2015-course
https://www.slideshare.net/siliconstudio/lenses-realtime-rendering-of-physically-based-optical-effect-in-theory-and-practice-siggraph-2015-course
https://www.slideshare.net/siliconstudio/making-your-bokeh-fascinating-realtime-rendering-of-physically-based-optical-effect-in-theory-and-practice-siggraph-2015-course

Motion Blur:
http://john-chapman-graphics.blogspot.com/2013/01/per-object-motion-blur.html
http://john-chapman-graphics.blogspot.com/2013/01/what-is-motion-blur-motion-pictures-are.html


Chromatic Aberration:
http://www.geeks3d.com/20101008/shader-library-chromatic-aberration-demo-glsl/


Toon Shading:
http://www.geeks3d.com/20140523/glsl-shader-library-toonify-post-processing-filter/


Edge Detection:
http://www.geeks3d.com/20110201/sobel-and-frei-chen-edge-detectors-demo-glsl/


Noise:
http://www.geeks3d.com/20100831/shader-library-noise-and-pseudo-random-number-generator-in-glsl/


SSAO:
http://john-chapman-graphics.blogspot.com/2013/01/ssao-tutorial.html


Subsurface Scattering:
https://www.alanzucconi.com/2017/08/30/fast-subsurface-scattering-1/


Depth of Field:
https://bartwronski.com/2014/04/07/bokeh-depth-of-field-going-insane-part-1/
http://gpupro.blogspot.com/2013/09/gpu-pro-4-skylanders-depth-of-field.html
http://fileadmin.cs.lth.se/cs/education/edan35/lectures/12dof.pdf
https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch23.html
http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
http://laplaciansplatting.mpi-inf.mpg.de/laplacian_splatting.pdf


Temporal Anti-Aliasing:
http://twvideo01.ubm-us.net/o1/vault/gdc2016/Presentations/Pedersen_LasseJonFuglsang_TemporalReprojectionAntiAliasing.pdf


Anti-Aliasing:
https://www.youtube.com/watch?v=b7dc3LwOUZc


Water:
https://www.youtube.com/watch?v=2AVh1x-Uqjs
