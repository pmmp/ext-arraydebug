--TEST--
Test handling of packed arrays
--DESCRIPTION--
Packed arrays aren't really hash tables, so they don't have any hash distribution.
In these cases we have to simulate.
--FILE--
<?php

$array = array_fill(0, 10, 0);
var_dump(array_hash_distribution($array));
var_dump(array_load_factor($array));

?>
--EXPECT--
array(10) {
  [0]=>
  array(1) {
    [0]=>
    int(0)
  }
  [1]=>
  array(1) {
    [1]=>
    int(0)
  }
  [2]=>
  array(1) {
    [2]=>
    int(0)
  }
  [3]=>
  array(1) {
    [3]=>
    int(0)
  }
  [4]=>
  array(1) {
    [4]=>
    int(0)
  }
  [5]=>
  array(1) {
    [5]=>
    int(0)
  }
  [6]=>
  array(1) {
    [6]=>
    int(0)
  }
  [7]=>
  array(1) {
    [7]=>
    int(0)
  }
  [8]=>
  array(1) {
    [8]=>
    int(0)
  }
  [9]=>
  array(1) {
    [9]=>
    int(0)
  }
}
float(1)
