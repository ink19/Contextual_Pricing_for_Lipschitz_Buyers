for i in range(1, 10):
    i = i * 3
    s = 0
    for j in range(1, i):
        # if i - j > j:
        #     s += 1
        for k in range(j + 1, i):
            if i -j - k > k:
                s += 1
            # for l in range(k + 1, i):
            #     if i - j - k - l > l:
            #         s += 1
    print(s)