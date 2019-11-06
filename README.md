# tinychain
a tiny blockchain for file storage and retrieval

# what?
tinychain is a dead-simple blockchain that stores text files (other file formats coming soonish)

# why?
it seemed like fun

# plans
* Serialization of Blocks to JSON
* Support for arbitrary file formats
* Support for multiple files on one blockchain
    * This could probably be done by splitting blocks into two types:
        * Data Blocks
            Stores the data of a part of a file.
        * Tracker Blocks
            Stores the block indicies of one file.
