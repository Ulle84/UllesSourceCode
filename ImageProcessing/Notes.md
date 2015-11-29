# ToDo
* return reference to image at functions which change the image content, i. e. erode dialte etc.

# Refactoring
* ImageT -> Layer
* Image -> map of layers: std::map<std::string, layer>
* Image is friend of layer -> full access
* ImageManager holds all instances of Image (friend) - display has a reference to ImageManager
* Class ImageProcessing, which implements all the algorithms - Image is friend of ImageProcessing
* Layer: member valid bits?
* Movie: List of Images

# Test
* dispaly images in gray and rgb
* display 12 bit images with range-slider
* Convert Image to QImage with formats: QImage::Format_RGB32 and QImage::Format_ARGB32

# Ideas
* implement move-constructor and move-operator -> copy from cImage and remove afterwards
* rectangle with orientation-angle
* drawEllipse - circle is also an ellipse
* polygon data type + drawFunction (polygon is a closed polyline) -> for filled polygons: Saatfül-Algorithmus
* teachIn (circle, line, rectangle, polygon)
* multi layer images
* add type region -> bit-mask for mopholgical operations
* crop image
* add noise to image
* look into Burger/Burge and implement some algorithms
* test openCV, generate converter for openCV
* contour tracing with pavlidis -> https://github.com/UnilVision/visionbase/blob/master/binary/contour%20tracing/Pavlidis/Pavlidis/pavlidis.c
* read from file
* write to file
* run length code
* rotate image with defined angle
* labeling
* blob analysis