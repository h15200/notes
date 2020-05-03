# flexbox

## CONTAINER

Flex-direction: row | column | reverse-row | reverse-column
Flex-wrap: nowrap | wrap | wrap-reverse
flex-flow: combo of flex-direction AND flex-wrap
Justify-content: flex-start | flex-end | center | space-between | space-around | space-evenly
align-items: stretch | flex-start | flex-end | center | baseline
align-content: stretch | flex-start | flex-end | center | space-between | space-around

// justify-content is on the main axis, align-items is on the cross axis, align-content only applies if there are more than 1 flex row, and they fit in the container

// space-around means it adds one “block” of space on both sides of each item. So for 2 items, it will divide space into 6 like below

Space Content Space space content space

// align-items default stretch will group the items together. For example, if one column is set to a height, the others will follow. Other align-item values will behave separately. Baseline will line up the TEXT of the item

// reverse direction will also make justify direction reversed!

## FLEX ITEMS

align-self: auto | stretch | flex-start | flex-end| center | baseline
order: 0
Flex (flex-grow: 0 is default, flex-shrink: 1 is default, flex-basis: auto)

How much to grow, how much to shrink, base size for each INDIVIDUAL item. These will take priority over any conflicting properties on the container.

If you are using a percentage for flex-basis, you can use 0 for both flex-grow and flex-shrink since it will do the shrinking based on percentage.

If you are using an absolute value in pixels or rems, better to use a grow/shrink value

## TEXT!

Flexbox also works with text inside an element! You can center a text inside an element using display flex, justify content and align items both to center!

## UNEVEN SPACING - MARGIN: AUTO

If you want some space next to a flex item, use margin-right: auto. This will make the flex item occupy only the amount of the content (unlike flex-grow)

If you want a flex row of 2 items occupy the entire row and 1 needs to be bigger than the other, simply put

.itemOne {
flex: 0 0 50%
}

.itemTwo {
flex: 1
}

If you put a margin between flex items, a cool move is to use the same amount on padding of the container so they are evenly spaced
