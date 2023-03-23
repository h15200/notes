class Solution:
    def calculate(self, s: str) -> int:
        stack = []
        prev_sign = "+"
        num = 0  # use to calculate digits
        for char in f"{s}+":  # needs one more sign to calculate last num
            if char.isdigit():
                num *= 10
                num += int(char)
            elif char in "+-*/":
                if prev_sign == "+":
                    stack.append(num)
                elif prev_sign == "-":
                    stack.append(-num)
                elif prev_sign == "*":
                    stack.append(stack.pop() * num)
                else:
                    stack.append(int(stack.pop() / num))
                num = 0
                prev_sign = char
        return sum(stack)
