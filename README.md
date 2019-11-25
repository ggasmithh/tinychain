# tinychain
a tiny blockchain for file storage and retrieval

# what?
tinychain is a dead-simple blockchain that stores files

# why?
it seemed like fun

# plans
* Serialization of Blocks to file
* ~~Support for arbitrary file formats~~
* add --add/-a, --remove/-r, and --update/-u flags to program
* Support for multiple files on one blockchain
    * This could probably be done by splitting blocks into two types:
        * Data Blocks
            Stores the data of a part of a file.
        * Tracker Blocks
            Stores the block indicies of one file.
