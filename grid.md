# Css grid

## GRID - 2 dimensional as opposed to flexbox being 1 demensional

TERMINOLOGY

Grid container
Grid item
Column axis (y) - Unlike Flexbox, they never shift orientation
Row axis (x)
Grid line- The outline of grid items that separate them. Always grid item per axis + 1
Ex. 3 x 4 grid item layout will have 4 horizontal grid lines x 5 vertical grid lines
Gutter - Space between grid items.
Grid Track - Space between an entire row or column.
Grid Row - a grid track on the x axis
Grid column - a grid track on the y axis
Grid Area - An area specified by grid lines
Grid Cell - a grid area that is divided by adjacent grid lines on both axis, the smallest unit
Implicit grid - An extra row or column of grid that is added with NO specified template because the content isn’t enough to fit in the explicit grid

## CONTAINER PROPERTIES

If a container does not specify width or height, the content will take up 100% of container

grid-template (grid-template-rows grid-template-columns grid-template-areas)
Grid-template-rows: 30px 30px 1fr; // the last row will take up all remaining space
grid-template-rows: repeat(5, 1fr) // each row is same size
grid-template-areas: “header header header header”
“main main main sidebar”
“main main main sidebar”
“footer footer footer footer”;

    // EACH Row is inside “   “

Every grid cell must be filled. If you want it empty, enter ‘ . ‘ so “main main . .”
The same component can NOT appear twice in a disjointed area. Must be connected. If not, just name them box-1 box-2 so “box-1 . box-2”

GRID UNIT - fr, span, -1
fr - Not an actual fraction or percentage. If you have 1fr 2fr 3fr, all three added, 6fr is the total capacity. It is then divided into each grid.
REMEMBER, 1fr will use available space to even up, but it will never cut off content. If grids are not equal despite having 1fr, then the content is more than the specified size

span - instead of grid-row: 1 / 3; you can also write grid-row: 1/ span 2;
A span bigger than the total number of available grid lines will create small, new grids

You can also span from the end by setting: span 3 / -1 // span 3 going backwards from the last line

-1 - when setting grid or column-row, if you forget the LAST grid line, you can just write -1
grid-row: 2 / -1; // make the item span over from row 2 all the way to the last existing row

-2 would be the 2nd from end line

This ONLY WORKS for explicit rows! Implicit rows will not work!

max-content, min-content, min-max(), auto-fill, auto-fit

Auto-fill/fit MUST use repeat and min-max!!

Grid-template-rows: max-content 1fr 1fr;

// will expand the row to fit all content in the widest way. Words will not break into a new line

// min-content will break words to that the row is smallest, but the columns will get bigger.

minmax(100px, min-content) // the grid is at least 100px and at most the min-context

Auto-fill and auto-fil are used for times when you want to be responsive without media queries.

Auto-fill - repeat(auto-fill, minmax(100px, 1fr)) // will fill the entire grid with as many grids as possible that are 100px each including empty grids

    Auto-fit // will create the max number of grids in the space, and get rid of extra cells without content

Usage:

Grid-template-columns: repeat(auto-fit, minmax(25rem, 1fr));
When a grid is squished below 25rem, a new row will appear.

Notice that unlike fr units, auto-fill and auto-fit will prioritize the division of grids based on width or height OVER the content fit. Content will be cut off in this method. You can NOT use fr units with auto-fill or auto-fit inside a repeat unless it’s inside a minmax() function

gap (row-gap column-gap)

Since grids are 2 dimensional and not 1 d like flexbox, you can justify AND align items
Just like flex, individual grid-items can override with justify-self and align-self

Justify-items stretch | center | start | end // horizontal placement of item
Align-items: stretch | center | start | end // vertical placement of item inside a grid area. For items that span vertically, the entire area will be considered 1 area

// -content is for positioning grid tracks (entire rows and columns) inside a container when the content does not take up 100%. Will not work if the container does not have a specified width (for justify-content) or height (for align-content) that is bigger than the grid tracks.

Justify-content: start | center | end | space-between | space-around | space-evenly
Align-content: start | center | end | space-between | space-around | space-evenly

Grid-auto-rows: typeOfNum // will size IMPLICIT rows that overflow from having too much content. Use if grid-auto-flow is default, “row”.
Grid-auto-columns: typeOfNum // same. Use if grid-auto-flow is set to “column”
Grid-auto-flow: row | column | row dense | column dense

    // Use dense to change the auto fill algorithm to avoid any holes. This will prioritize filling up space over preserving the html element order. Useful for a gallery where order is not important

    Since grid-auto-flow is set to “row” by default, all overflow grid will become new ROWS, so grid-auto-rows will take effect. If grid-auto-flow is set to “column”, then grid-auto-columns should be set.

## ITEM PROPERTIES

To rearrange grid items, you can do it by specifying grid lines via grid-area (or grid-row and grid-column) Try not to ever use grid-row-start and opt for shorthand grid-row, but grid-area is a bit confusing so might be better not to use.

    OR you can use “order” like in flexbox.

Grid-row: 2 / 3; (shorthand for grid-row-start, grid-row-end)
grid-column: 1 / -1 // start at 1, go to end of available grids

Grid-area: header; // NOTICE that in this property, no quotation marks!
(grid-area can also be used as shorthand for grid-row AND grid-column, but DO NOT use it that way as it is confusing)

Justify-self: stretch | self-start | self-end | center
Align-self

Order - default on “1”, change to switch order

// If you explicitly tell 2 items to be in an overlapping area, they will be on top of each other. If not, the grid-item with more specificity will take priority and shift the other item

## NAMING GRID LINES

When setting templates in the container, you can also name the lines by inserting [namedLine] before AND after the specified unit.

Grid-template-rows: [header-start] 100px [header-end main-start] 200px [main-end footer-start] 100px [footer-end] ;

Then in individual grid items,

.main {
grid-row: main-start / main-end;

// you can name grid lines with []. Like classes, you can name the same line with 2 names
// usually a good idea to do so at least for ROWS

To name lines inside a repeat function:

Grid-template-column: repeat(3, 1fr) // becomes:

Grid-template-column: repeat(3, [line-start-name] 1fr [line-end-name])

//Since there will be identical names, CSS will RENAME to [line-start-name 1], [line-start-name 2] etc.. NOTICE THE WHITESPACE before the index number!

## RESPONSIVE GRID

A great trick is to use:
// This whole area should already have a max-width parameter in some way

grid-template-columns: repeat(auto-fit, minmax(25rem, 1fr));
// or auto-fill

// the min should be set to a number that gives you the desired INITIAL number of columns. Then resizing should make it responsive

## WORKFLOW

Figure out basic design, then the number of grid lines.
Figure out what makes the most sense between naming lines by default numbers, names, or areas. Template areas are great for SMALL grid systems

Make div.container

Treat the entire site as 1 grid, and each section being a grid-item

Setting no templates will default to having rows and 1 column

    Rows

Really think about responsiveness from the beginning, especially for COLUMNS! The nexter project used something like

grid-template-rows: 80vh min-content 40vw repeat(3, min-content);

    Columns - common to use 8 or 12 column grid systems
    Use a minmax function on the column to get the max-width of the main content

Grid-template-columns: repeat(8, minmax(min-content, 8.75rem)); // 8.75rem = 140px, which is 1,120px divided by 8 cols.

You should name the columns as well, so

grid-template-columns: [sidebar-start] 5rem [sidebar-end full-start] minmax(3.75rem, 1fr) [center-start] repeat(8, [col-start] minmax(min-content, 8rem) [col-end]) [center-end] minmax(3.75rem,1fr) [full-end];

Often a good idea to set the bare essentials in template, like just the column and let the content decide the row height. No need to set both dimensions explicitly every time.

You can set grid-row and grid-column on grid items WITHOUT a template on the container, but remember that -1 is only for the last line of the EXPLICIT row or columns.

## IMAGES IN GRID

When using images, the aspect ratio will be prioritized and will not stretch into grid containers.

## IMAGE - FLOW OUT OF CONTAINER

A hack to go outside the grid is to simply use width: 115%;

## UNEVEN GAPS

There is no way to style an individual grid-item’s gap property, so use margins

## OBJECT-FIT: COVER;

Object-fit is usually used on the CONTAINER of images to override aspect ratio prreservation and fill out the container. In Gatsby-images, containers already exist and the classname on the <Img> is on the container itself, so you can put use object-fit directly.

If you’re using object-fit: cover, make sure to include width: 100% AND height: 100%

With gatsby you may also not need object-fit at all.

## USE IMPLICIT GRIDS!

Often times, the solution is to NOT do anything. If you want something like this in an 80vh component

1

3
4
5

Then all you need is grid-template-rows: 1fr;
// First item gets all remaining area after content for 3,4,5 is filled

Then, as you NEED more info, go back and fill out the template. For example if you want more space around item 4, then go back and do

Grid-template-rows: 1fr, min-content, 10rem (or something);

## GATSBY IMAGES AND GRID

I DON’T KNOW WHY but align-items (to anything) will fix cropping problems!

## GRID-ITEM AS TEXT

Just as in flexbox, even a single div can become a grid-container if there is text

## LIMITS OF MINMAX

If the max unit is responsive and becomes smaller than the min unit, it will be ignored.
