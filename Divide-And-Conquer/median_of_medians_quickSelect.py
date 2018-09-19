A = list(map(int, input().split()))
def select(A, low, high, index):
    if low==high:
        return A[low]

    medians = []

    for i in range(low, high + 1, 5):
        if i + 4 <= high:
            medians.append(sorted(A[i: i+5])[2])
        else:
            medians.append(sorted(A[i: high + 1])[(high + 1 - i)//2])

    #print(medians, A[low: high + 1])
    median_of_medians = select(medians, 0, len(medians) - 1, len(medians) // 2)
    median_of_medians = low + A[low:high + 1].index(median_of_medians)
    #print(median_of_medians)
    A[high], A[median_of_medians] = A[median_of_medians], A[high]

    pivot = A[high]
    k = low
    for j in range(low, high):
        if A[j] < pivot:
            A[k], A[j] = A[j], A[k]
            k += 1

    A[high], A[k] = A[k], A[high]
    #print(k, index)
    if index==k:
        return A[k]
    elif index < k:
        return select(A, low, k - 1, index)
    else:
        return select(A, k + 1, high, index) 

for i in range(0, len(A)): 
    print(select(A, 0, len(A) - 1, i))
