# Bugs

# ToDo (prioritised)
* Debugger must be usable!!!
* edge detection -> first horizontal, then vertical, then with any angle
  * input
    * vector (startpoint, direction, length)
    * filterWidth for smoothing
    * Pixel-Abstand für die Differenzbildung
    * minimum contrast
    * edge type (bright,dark,any)
  * idea
    * Linie definieren
    * länge der linie (in Anzahl Pixeln) bestimmen -> buffer anlegen
    * entlang der Linie für jeden Punkt
      * die Senkrechte bilden
      * symmetrisch um den Punkt entlang der senkrechten den mittelwert bilden -> Mittelwertslinie
    * entlang der Mittelwertslinie Differenzen bilden (mit Pixel-Abstand für die Differenzbildung)
    * schuen welche Differenzen die Kontastvorgaben (Wert, Typ) erfüllen
    * Ergebnis-Vektor mit Kanten zurückgeben, ggf. gefunden Kanten markieren
  * class Point -> startPoint x and y -> double
  * Class Vector -> startPoint, direction, length (may be negative!)
  * Class Edge derived from Vector - as long as there are no differences between vetor and edge -> typedef
  * Matrix: double getAverageAlongLine(const Line& line)
  * Class: Edges
    * list of edges
    * getFirstEdge(edgeType: bright,dark,any)
    * getLastEdge(edgeType: bright,dark,any)
    * getEdgePairs ???
  * line fit -> input: points - output: line - take care of special cases (link vertical line)
* calculate statistics for runLengthCode or wohle image if nullptr
* Hole-Filling -> see handwritten notes of 2015-12-13
* Matrix::setStructureElement(T value, Point (where the reference point of the structureElement is placed) ...)
* invert operator (!) for StructuringElements
* operators + += etc. see pic.h/cpp
* use exceptions?
* serialization of matrix
* buttons for display zoom to use disply with one hand
* auto-zoom on show image
* Look at ToDos in Source-Code and change to // IP if appliable
* implement move-constructor and move-operator -> copy from cImage and remove afterwards -> test, that the move-constructor and move-operator are called, when possible
* return reference to image at functions which change the image content, i. e. erode dialte etc.
  * test that move-constructor and move-operator are used, otherwise this operations will be very "expensive"
  * test: imageEroded = image.erode(blub);
  * test: image = image.erode(blub);
* define reference point for rotation with angle: top-left-corner vs. center
* Matrix: squeeze function -> delete all conversion-buffers, which are not needed anymore
* convolution of two matrices / vectors

# Ideas
* rectangle with orientation-angle
* drawEllipse - circle is also an ellipse
* polygon data type + drawFunction (polygon is a closed polyline) -> for filled polygons: Saatfül-Algorithmus
* interactive teachIn
  * circle
  * line
  * rectangle
  * polygon
* add noise to image (salt and pepper, standard-deviation noise)
* look into Burger/Burge and implement some algorithms
* test openCV, generate converter for openCV
* contour tracing with pavlidis -> https://github.com/UnilVision/visionbase/blob/master/binary/contour%20tracing/Pavlidis/Pavlidis/pavlidis.c
* write to file
* rotate image with defined angle
* labeling
* blob analysis
* ImageManager: holds references to Images - display has a reference to ImageManager -> own Application with shared memory
* 16 bit images -> ImageViewer has a range-slider, where the displayed bits can be selected
* datamatrix code
  * create
  * read generated
  * test: change some pixels and try to read
* type: line -> 2 points define a line: Alternative: start point, angle + length
* setInterpolationMode: nearestNeighbor, bilinearInterpolation, ...?
* setNeighborhood: neighborhood4, neighborhood8
* patter matching
* statistics on objects (mean value etc)
* floodFill: https://de.wikipedia.org/wiki/Floodfill
* implement more filters: http://homepages.inf.ed.ac.uk/rbf/HIPR2/filtops.htm
* hough transformation
* fourier transformation
* rectification -> 4 Points given -> check that no point is in triangle of other 3 points -> rectify
* classification
* print text inside image
* convex hull

# Applications
* Count Eyes of Dice
* detect gap between stopper and vial
* Homogenitätsanalyse ->
* find circle countour and fit circle
* count coins, analyse coins and calculate value

# Documentation
## General
* Comments
  * // IP -> improve performance
  * // TODO -> ToDo
  * // TBD -> to be discussed/decided/done
  * // BUG -> Bug, which needs to be fixed
  * // NTH -> nice to have
* vector of mixed types is not possible, so a vector of a template with different initialisations is also not possible -> Image with different Layers (int, double, bool) is currently not possible
* Best approach of some hours of testing: Base Template Class (3d)Matrix + Derivations (ImageGray, ImageRGB, etc)
* Matrix is template base class, all algorithms which are type-independent are defined here

## Goals (ordered)
* correctnes
* no code duplication
* clearance
* high performanace
* low memory consumption

## Mindestanforderungen BV Software
* Morphologie (Binär und Grauwert)
* Faltung oder alternativ Sobel-, Laplace- und Gauss-Filter
* Kantendetektoren z. B. Canny
* Bildarithmetik
* Fouriertransformation
* Labeling
* Statistische Features (Mittelwert, Varianz etc.)
* Einfache Segmentierung (Thresholding, Wasserscheide etc.)
* Ein Klassifikator

## Matrix and FilterMask
* FilterMask should inherit from Matrix
* code duplication should be avoided
* FilterMask as friend of Matrix is not possible
* template <typename FT, typename MT> class FilterMask : Matrix<FT> -> not possible - error-message: cannot cast FilterMask<int, unsigend char> to its private base class Matrix<int>
* template <typename T> class FilterMask : Matrix<double> with function void apply(Matrix<T>* matrix); -> also not possible
* template<typename F, typename M> void filterMatrix(Matrix<M>* matrix, Matrix<F>* filter, const Point& referencePoint, double preFactor = 1.0, unsigned z = 0) -> also not possible: no matching fucntion for call to filterMatrix
* template<typename T> void filterMatrix(Matrix<T>* matrix, FilterMask* filter, double preFactor = 1.0, unsigned z = 0) : no matching fucntion for call to filterMatrix
* Solution FilterMask is defined in Matrix and inherits from Matrix<short>

## Restrictions
* m_height * m_width must be smaller than max possible value of unsigned int
