# Bugs

# ToDo (prioritised)
* remember directory of last file selection
* Look at ToDos in Source-Code and change to // IP if appliable
* Display-Information: Decide between gray and color image
* implement template Matrix -> move functionality from Image
* implement move-constructor and move-operator -> copy from cImage and remove afterwards -> test, that the move-constructor and move-operator are called, when possible
* Image
  * create class Image which inherits from Matrix<unsigned char> -> test that move-constructor and move-operator of Matrix is used
* return reference to image at functions which change the image content, i. e. erode dialte etc.
  * test that move-constructor and move-operator are used, otherwise this operations will be very "expensive"
  * test: imageEroded = image.erode(blub);
  * test: image = image.erode(blub);
* define reference point for rotation with angle: top-left-corner vs. center
* Matrix: squeeze function -> delete all conversion-buffers, which are not needed anymore

# Ideas
* rectangle with orientation-angle
* drawEllipse - circle is also an ellipse
* polygon data type + drawFunction (polygon is a closed polyline) -> for filled polygons: Saatfül-Algorithmus
* interactive teachIn
  * circle
  * line
  * rectangle
  * polygon
* add type region -> bit-mask for mopholgical operations -> instance of Matrix<bool>
* crop image
* add noise to image
* look into Burger/Burge and implement some algorithms
* test openCV, generate converter for openCV
* contour tracing with pavlidis -> https://github.com/UnilVision/visionbase/blob/master/binary/contour%20tracing/Pavlidis/Pavlidis/pavlidis.c
* write to file
* run length code
* rotate image with defined angle
* labeling
* blob analysis
* ImageManager: holds references to Images - display has a reference to ImageManager
* 16 bit images -> ImageViewer has a range-slider, where the displayed bits can be selected
* datamatrix code
  * create
  * read generated
  * test: change some pixels and try to read
* type: line -> 2 points define a line: Alternative: start point, angle + length

# Documentation
* Comments
  * // IP -> improve performance
  * // TODO -> ToDo
  * // TBD -> to be discussed/decided/done
  * // BUG -> Bug, which needs to be fixed
  * // NTH -> nice to have
* vector of mixed types is not possible, so a vector of a template with different initialisations is also not possible -> Image with different Layers (int, double, bool) is currently not possible
* Best approach of some hours of testing: Base Template Class (3d)Matrix + Derivations (ImageGray, ImageRGB, etc)
* Matrix is template base class, all algorithms which are type-independent are defined here
