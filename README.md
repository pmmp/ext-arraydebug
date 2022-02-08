# ext-arraydebug
Debug functions for PHP arrays to calculate things like hash distribution and other internal information

## Array load factors and hash collisions
### What is a hash collision?

Arrays in PHP (when they are not using linear keys) are stored as a hashmap. The hash used is either a user-provided integer (unmodified) or a rolling string hash when string keys are used.
Depending on the number of keys, the table size used for the hash table varies.

The table is indexed by taking a certain number of the least significant bits of the key hash (or the naked key value, in the case of integers).
**This means that if your keys have poor distribution in the least significant bits, many hash collisions will occur.**

### Why are hash collisions bad?
Hash collisions in PHP arrays can be a major performance bottleneck which isn't obvious to the eye.

When two different keys produce the same hash, they are stored in a linked-list under that hash. When the hash is looked up, PHP then has to traverse **every element** of this linked-list one by one to find the actual matching key.
When the array has a high number of hash collisions, these linked lists can get very long, resulting in a long brute-force search every time an array key is accessed.

The average length of these lists is known as the **load factor**, and gives us an idea of just how much the performance will suffer because of this.
Ideally we want our load factor to be as close to 1 as possible, to avoid the bruteforce searches we just mentioned.

### Examples
For example, the following code:
```php
$array = [];

for($i = 0; $i < 10000; $i++){
	$array[$i << 1] = $i;
}
```
produces an array with a load factor of 1, while this code:
```php

$array = [];

for($i = 0; $i < 10000; $i++){
	$array[$i << 10] = $i;
}
```
has a load factor of 312.5!

This means that, despite having the same number of keys, accesses to the second array will be significantly slower than the first.
