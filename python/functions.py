# functions

def get_highest_char(str)->str:
    return max(str) # max returns the last char in abc order
  
# print(get_highest_char('abcdflkjad;skfjwijuzzz234LKJFDLKj&')) # prints "z"



def get_highest_num(nums):
  curr_lowest = None
  for num in nums:
    if curr_lowest == None or num < curr_lowest:
      curr_lowest = num
  return curr_lowest

# print(get_highest_num([1,2,3,4,5,6,-2])) # prints -2