# Fix Doubly Linked List Reversal Corrupting `prev` Pointers

## Description
This PR addresses Issue #248, where the Doubly Linked List (DLL) reversal logic (`dll_reverselist`) in `src/data_structures/dll.c` was incorrectly implemented. The previous logic only reversed the `next` pointers (similarly to a Singly Linked List) and ignored the `prev` pointers, corrupting the list's backward links.

The `dll_reverselist` function has been rewritten to properly swap the `prev` and `next` pointers for each node, ensuring that the fundamental property of the doubly linked list remains intact after a reversal.

## Changes
- Rewrote `dll_reverselist` in `src/data_structures/dll.c` to swap `prev` and `next` pointers.
- Handled the edge cases (empty list and single-node list) consistently.

## Related Issues
Fixes #248
