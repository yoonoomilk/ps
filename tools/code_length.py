import clipboard

print(sum([1 if ord(i) < 256 else 3 for i in clipboard.paste()]))