title(SimpleHTML)

SimpleHTML
* Ziel: einfach, einheitlich, kompakt und schnell schreiben, ohne viel neue Syntax zu erlernen.
* Output: HTML
* Kein Tag-Overhead
* Fallback zu normalem HTML jederzeit möglich

Drawbacks of HTML
* moving listitems in hierarchies complicated
* annoing use of < and >
* lot of overhead because of opening and closing tags
* highlighting support of most editors is bad

Regeln:
* Runde Klammern müssen immer paarweise auftreten! (Die Regel kann abgeschafft werden, wenn Runde Klammern escape-fähig sind)
* Tags innerhalb eines Code-Tags werden ignoriert

Festlegungen
* keine Shortcuts -> Einheitlichkeit an vorderster Stelle - Support für schnelles Schreiben durch Editor und Code-Vervollständigung
* wenn in Tabelle - Tabellen-Editor Shortcut (cmd+e) aufrufen
* wenn in Liste -> Listen-Editor per Shortcut aufrufen

Syntax benötigt für:
* Überschriften
* Listen
* Bilder
* Inline-Code
* Code-Blöcke
* Tabellen
* Text-Formatierungen
* Kommentare

Tags - all HTML tags can be used - additional tags
* tableh -> table where the first line is interpreted as header content
* c - code
* cpp - cpp code
* toc - table of content
* toi - table of images
* tot - table of tables

Syntax
tag((optionalOption1=blub)(optionalOption2=foo)visible text)

h1(Chapter)
h2(Section)

ol(ordered list item one
ordered list item two
  nested ordered list item one
  nested ordered list item two)

ul(unordered list item one
unordered list item two
  nested unordered list item one
  nested unordered list item)

code((language=cpp)code line one
code line two

code line three)

table(line 1 col 1 | line 1 col 2
line 2 col 1 | line 2 col 2)

tableh(header col 1 | header col 2
line 1 col 1 | line 1 col 2
line 2 col 1 | line 2 \| col 2)

img((src=path\to\image.png))
img((width=300)(border=3)(padding=20)(src=path/to/image))

a((href=www.test.de)test) - displayed as test
a((href=www.test.de)) - displayed as www.test.de

marker inside text: b(this text is bold) c(this is code) i(this is italic) s(this is strong) i(italic text b(italic bold text) and italic text again)

Syntaxhighlighting
* ( and corresponding )
* Tags
* Attributes + Values

Escape Sequences
* '|' (Escaping only necessary inside tables)
* maybe for ( and ) neccessary: '(' and ')'

ToDos/Ideas
* SimplifiedHtmlConverter
  * write te tests for converter
  * options((foo=true)(blub=false))?
  * escape to HTML symbols & for example
* SimplifiedHtmlViewer
* SimplifiedHtmlEditor
  * Opening bracket is automatically completed by closing bracket, except, if inside ''.
  * If the cursor is directly next to opening bracket the closig bracket is highlighted
  * If the cursor is directly next to closing bracket, the opening bracket and corresponding keyword is highlighted.
  * Use different colors for bracket highlighting: option brackets have another color than tag brackets, normal brackets have a third color.
  * Special support for lists and tables
  * Strg+Shift+Up/Down - moves current line up/down and takes care that only content in lists an tables are moved (keywords and options stay in place)
  * Hover over image path shows preview
  * Show error, if number of opening brackets is not the same than the number of closing brackets (background is colored lightly red)
  * Ctrl+Click on link opens link in default browser
  * highlight doubled defined options in red - example: div((width=400)(border=true)(width=500)some text. Options for width are conflicting) - hovering over highligted text shows problem
  * highlight if some tags are define doubled, for example the title-tag. 
  * preview on hover over table/image/link
  * different colors for different columns inside table (use some different colors, which are doubled if table gets very wide)
  * block highlighting: tables and lists etc. are highlighted
  * code completion
    * a + opening bracket becomes to a((href=))
    * img + opening bracket becomes to img((src=))
  * right click on table -> show table editor
  * code highlighting
    * table headers
    * source code
  * automatic indentation
  * implement zoomIn/Out -> available for QTextEdit
  * drag and drop an image to text
  * line numbers http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
  * highlight current line http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
  * mark h1-h6 in seperate color
  * create clickable table of content

h1(Test)
h2(blub)
This is some text. Let's say I want to write about the new b(C++11) standard.
C++ has a cool new b(keyword): c(nullptr).
Instead of writing a implicit c(NULL) or c(0) you now have a explicit expression: c(nullptr).

img(this/is/a/image.png)

img((widht=300)(border=true)(src=this/is/a/shrinked/image/with/an/added/border.png))

code((language=cpp)this is a code block
with C++ CodeHighlighting)

cpp(this is also a code block
with c++ syntax)

hr()

The line above should be a horizontal line.
You can force br() a new line inside a line.

Here is a list of links
ul(a((href=www.google.de)Google)
a((href=www.heise.de)Heise)
a(www.directLink.com))

table(line col 1 | line 1 col 2
line 2 col 1 | line 2 col 2)

tableh(header 1 | header 2
line col 1 | line 1 col 2
line 2 col 1 | line 2 col 2)


List of all HTML Tags
<!--...-->	Defines a comment
<!DOCTYPE> 	Defines the document type
<a>	Defines a hyperlink
<abbr>	Defines an abbreviation or an acronym
<acronym>	Not supported in HTML5. Use <abbr> instead.
Defines an acronym
<address>	Defines contact information for the author/owner of a document
<applet>	Not supported in HTML5. Use <embed> or <object> instead.
Defines an embedded applet
<area>	Defines an area inside an image-map
<article>	Defines an article
<aside>	Defines content aside from the page content
<audio>	Defines sound content
<b>	Defines bold text
<base>	Specifies the base URL/target for all relative URLs in a document
<basefont>	Not supported in HTML5. Use CSS instead.
Specifies a default color, size, and font for all text in a document
<bdi>	Isolates a part of text that might be formatted in a different direction from other text outside it
<bdo>	Overrides the current text direction
<big>	Not supported in HTML5. Use CSS instead.
Defines big text
<blockquote>	Defines a section that is quoted from another source
<body>	Defines the document's body
<br>	Defines a single line break
<button>	Defines a clickable button
<canvas>	Used to draw graphics, on the fly, via scripting (usually JavaScript)
<caption>	Defines a table caption
<center>	Not supported in HTML5. Use CSS instead.
Defines centered text
<cite>	Defines the title of a work
<code>	Defines a piece of computer code
<col>	Specifies column properties for each column within a <colgroup> element 
<colgroup>	Specifies a group of one or more columns in a table for formatting
<datalist>	Specifies a list of pre-defined options for input controls
<dd>	Defines a description/value of a term in a description list
<del>	Defines text that has been deleted from a document
<details>	Defines additional details that the user can view or hide
<dfn>	Represents the defining instance of a term
<dialog>	Defines a dialog box or window
<dir>	Not supported in HTML5. Use <ul> instead.
Defines a directory list
<div>	Defines a section in a document
<dl>	Defines a description list
<dt>	Defines a term/name in a description list
<em>	Defines emphasized text 
<embed>	Defines a container for an external (non-HTML) application
<fieldset>	Groups related elements in a form
<figcaption>	Defines a caption for a <figure> element
<figure>	Specifies self-contained content
<font>	Not supported in HTML5. Use CSS instead.
Defines font, color, and size for text
<footer>	Defines a footer for a document or section
<form>	Defines an HTML form for user input
<frame>	Not supported in HTML5.
Defines a window (a frame) in a frameset
<frameset>	Not supported in HTML5.
Defines a set of frames
<h1> to <h6>	Defines HTML headings
<head>	Defines information about the document
<header>	Defines a header for a document or section
<hr>	Defines a thematic change in the content
<html>	Defines the root of an HTML document
<i>	Defines a part of text in an alternate voice or mood
<iframe>	Defines an inline frame
<img>	Defines an image
<input>	Defines an input control
<ins>	Defines a text that has been inserted into a document
<kbd>	Defines keyboard input
<keygen>	Defines a key-pair generator field (for forms)
<label>	Defines a label for an <input> element
<legend>	Defines a caption for a <fieldset> element
<li>	Defines a list item
<link>	Defines the relationship between a document and an external resource (most used to link to style sheets)
<main>	Specifies the main content of a document
<map>	Defines a client-side image-map
<mark>	Defines marked/highlighted text
<menu>	Defines a list/menu of commands
<menuitem>	Defines a command/menu item that the user can invoke from a popup menu
<meta>	Defines metadata about an HTML document
<meter>	Defines a scalar measurement within a known range (a gauge)
<nav>	Defines navigation links
<noframes>	Not supported in HTML5.
Defines an alternate content for users that do not support frames
<noscript>	Defines an alternate content for users that do not support client-side scripts
<object>	Defines an embedded object
<ol>	Defines an ordered list
<optgroup>	Defines a group of related options in a drop-down list
<option>	Defines an option in a drop-down list
<output>	Defines the result of a calculation
<p>	Defines a paragraph
<param>	Defines a parameter for an object
<pre>	Defines preformatted text
<progress>	Represents the progress of a task
<q>	Defines a short quotation
<rp>	Defines what to show in browsers that do not support ruby annotations
<rt>	Defines an explanation/pronunciation of characters (for East Asian typography)
<ruby>	Defines a ruby annotation (for East Asian typography)
<s>	Defines text that is no longer correct
<samp>	Defines sample output from a computer program
<script>	Defines a client-side script
<section>	Defines a section in a document
<select>	Defines a drop-down list
<small>	Defines smaller text
<source>	Defines multiple media resources for media elements (<video> and <audio>)
<span>	Defines a section in a document
<strike>	Not supported in HTML5. Use <del> or <s> instead.
Defines strikethrough text
<strong>	Defines important text
<style>	Defines style information for a document
<sub>	Defines subscripted text
<summary>	Defines a visible heading for a <details> element
<sup>	Defines superscripted text
<table>	Defines a table
<tbody>	Groups the body content in a table
<td>	Defines a cell in a table
<textarea>	Defines a multiline input control (text area)
<tfoot>	Groups the footer content in a table
<th>	Defines a header cell in a table
<thead>	Groups the header content in a table
<time>	Defines a date/time
<title>	Defines a title for the document
<tr>	Defines a row in a table
<track>	Defines text tracks for media elements (<video> and <audio>)
<tt>	Not supported in HTML5. Use CSS instead.
Defines teletype text
<u>	Defines text that should be stylistically different from normal text
<ul>	Defines an unordered list
<var>	Defines a variable
<video>	Defines a video or movie
<wbr>	Defines a possible line-break



Input Backup
h1(hello world)
h2(test)

p(a((href=http://www.google.de)a link to google))

p(writing HTML is so b(comfortable) and b(easy!))

pre((style=background-color: lightblue)
some code
over two lines
what about a method
)

p(here is some code(code inside the text))


hr()
table(
  tr(th(header 1) th(header2))
  tr(td(line 1, column 1) td(line 1, column 2))
  tr(td(line 2, column 1) td(line 2, column 2))
)

ul(
li(test)
li(test2)
li(subtest)
  ul(
   li(subtest)
  )
)

ol(
  li(test)
  li(test2)
)
