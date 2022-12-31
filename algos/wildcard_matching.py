class Solution:
    # always do a decision tree

    # the 2  major conditional is the * on 2nd index and if it's a match
    # the other gotcha is that if s is out of bounds and p isn't, that's ok!
    # if p is out of bounds and s isn't that will always be False
    # s , x*(rest)
    # /       \
    # if match, s[2:], rest,      s, rest

    def isMatch(self, s: str, p: str) -> bool:
        cache = {}  # tuple key of (s, p): True
        print("inputs are", s, p)

        def recurse(si: int, pi: int) -> bool:
            print("recurse func: s, p", s[si:], p[pi:])
            if (si, pi) in cache:
                return cache[(si, pi)]
            if si >= len(s) and pi >= len(p):
                return True
            if pi >= len(p):
                return False
            match = si < len(s) and (s[si] == p[pi] or p[pi] == ".")
            star = pi + 1 < len(p) and p[pi + 1] == "*"
            # scenarios
            # if match and star
            # if match and no star
            # if not match and star
            # if not match and no star
            if match and not star:
                return recurse(si + 1, pi + 1)
            elif match and star:  # take the two paths
                cache[(si, pi)] = recurse(si, pi + 2) or recurse(si + 1, pi)
                return cache[(si, pi)]
            elif not match and star:
                cache[(si, pi)] = recurse(si, pi + 2)
                return cache[(si, pi)]
            elif not match and not star:
                cache[(si, pi)] = False
                return False

        return recurse(0, 0)
