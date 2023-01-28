# functions


def main():
    def get_highest_char(str) -> str:
        return max(str)  # max returns the last char in abc order

    # print(get_highest_char('abcdflkjad;skfjwijuzzz234LKJFDLKj&')) # prints "z"

    def get_highest_num(nums):
        curr_lowest = None
        for num in nums:
            if curr_lowest is None or num < curr_lowest:
                curr_lowest = num
        return curr_lowest

    # print(get_highest_num([1,2,3,4,5,6,-2])) # prints -2

    def flatten_list(nested_list) -> list:
        def recurse(input) -> None:
            for item in input:
                if isinstance(item, list):
                    recurse(item)
                else:
                    output.append(item)

        output = []
        recurse(nested_list)
        return output

    print(flatten_list([1, 2, 3]))
    print(flatten_list([1, [[[2]]], 3]))
    print(flatten_list(["a", ["bb", ["ccc", "ddd"], "ee", "ff"], "g", "h"]))


test = [1, 2, 3]


if __name__ == "__main__":
    main()
