# using args in for loops <starting, ending, increment>

for i in ['a', 'b']:
  print(i) # prints the actual List items


nums = [10,20,30]
for i in range(len(nums) - 1, -1, -1):
  print('item is', nums[i])

# input, string template literal with `f` for formatted string literal
# try/except dangerous blocks of code


try:
  age = int(input('what is your age?\n')) 
except:
  age = - 1
if (age >= 0 and age < 150):
  print(f'that\'s fantastic that your age is {age}')
else:
  print('Input must be a valid integer')
    

