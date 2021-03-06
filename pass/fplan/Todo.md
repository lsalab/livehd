Tests:
 - clocked logic
 - 500K XOR table

Big refactor:
 - Group a collapsed hier, pattern, etc. into a "slice" that is totally contained in a single thread
     this is also going to make the code a ton faster because >1 thing can be done at once and better cache locality
 - Make sure that connectivity information is kept throughout the floorplan generation process since that information is required at the end

Optimizations:
 - area adjustment algorithm is naive, and inserts area when it isn't necessary
 - preloading vectors with sizes known ahead of time could save some time
 - check to see if graph lib has fast functions to do what I'm doing myself
     sets -> subgraphs
 - beware of temporaries
 - when making maps, see if I can use references instead of actual copies - might be a lot cheaper!

Style guide refactors:
 - make sure all class/type names are uppercase
 - set/map -> absl versions
 - const string& as a parameter -> string_view
 - string ops -> abseil versions
 - '_' to seperate words
 - make variable names less wordy
 - C++14 iterators?
 - const vector& -> absl::Span
 - getters and setters (check style guide!)

Code improvements:
 - pair of vectors -> map if more readable
 - const <type>& -> &&
 - for loops -> ranges
 - take out '&' if not used
 - uniform frequency of comments
 - Hier_tree is starting to become kinda monolithic.  This is prob okay, since graph objects are super hard to move.
     Make sure that things are as decoupled as possible - private globals aren't readable.
     We can return literals, and as long as we use move semantics we'll be fine on speed. 
 - Node/vertex/vert/module terminology is inconsistant
 - only need <functional> if doing a recursive lambda
 - dag could probably be an ordered set

Long term:
1. some sort of check() method that verifies netlists and internal functionality
2. a way to call BloBB or CompaSS directly, since they're way faster than HiReg
   (1 sec on a test floorplan vs 15 sec for HiReg, according to the HiReg paper)

Tried:
 - namespaces: none of the other passes are namespaced so whatever
