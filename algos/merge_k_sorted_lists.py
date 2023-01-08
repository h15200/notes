# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeKLists(self, lists):

        # much faster to merge 2 lists k times rather than doing 1 merge k * 2 times. why?
        # when merging 2 lists, you go until one is done, and simply chain the entire rest to the other

        if len(lists) == 0:
            return None

        while len(lists) > 1:
            # continually merge only 2 links at a time until 1 is left
            temp = []
            for i in range(0, len(lists), 2):
                list_1 = lists[i]
                list_2 = lists[i + 1] if i + 1 < len(lists) else None  # could be end of list
                temp.append(self.merge_two(list_1, list_2))
            # update the main list with the new halved sorted list
            lists = temp
        # only one final list left, which is the answer
        return lists[0]

    def merge_two(self, list_1, list_2):
        if list_1 is None:  # original list could have None instead of a list
            return list_2
        if list_2 is None:
            return list_1

        dummy = ListNode(0)
        curr = dummy

        while list_1 and list_2:
            if list_1.val < list_2.val:
                curr.next = ListNode(list_1.val)
                list_1 = list_1.next
            else:
                curr.next = ListNode(list_2.val)
                list_2 = list_2.next
            curr = curr.next

        # if one is None and the other exists
        if list_1:
            curr.next = list_1
        elif list_2:
            curr.next = list_2

        return dummy.next
