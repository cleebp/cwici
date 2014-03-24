#!/usr/bin/perl

$line1 = "./cwici test2.wic > test2.out";
print "$line1\n";
system $line1;

$line2 = "diff -b -B test2.wic test2.out > test2.diffs";
print "$line2\n";
system $line2;
