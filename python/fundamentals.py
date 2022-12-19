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
  print('Input must be a valid integer')
  quit()

if (age <= 0 or age > 150):
  print('Must be a realistic age!')
  quit()
print(f'that\'s fantastic that your age is {age}')

    

