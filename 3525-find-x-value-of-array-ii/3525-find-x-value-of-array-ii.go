const MAXN = 100_000 + 1
const MAXK = 5 + 1

var tree [2*MAXN*MAXK + MAXK]uint32

func merge(l, r, i, k int) {
	mul := int(tree[l+k])
	tree[i+k] = uint32(mul) * tree[r+k] % uint32(k)
	switch k {
	case 1:
		tree[i] = tree[l] + tree[r]
	case 2:
		tree[i] = tree[l] + tree[r]
		tree[i+1] = tree[l+1]
		tree[i+(mul*1)%2] += tree[r+1]
	case 3:
		tree[i] = tree[l] + tree[r]
		tree[i+1] = tree[l+1]
		tree[i+2] = tree[l+2]
		tree[i+(mul*1)%3] += tree[r+1]
		tree[i+(mul*2)%3] += tree[r+2]
	case 4:
		tree[i] = tree[l] + tree[r]
		tree[i+1] = tree[l+1]
		tree[i+2] = tree[l+2]
		tree[i+3] = tree[l+3]
		tree[i+(mul*1)%4] += tree[r+1]
		tree[i+(mul*2)%4] += tree[r+2]
		tree[i+(mul*3)%4] += tree[r+3]
	case 5:
		tree[i] = tree[l] + tree[r]
		tree[i+1] = tree[l+1]
		tree[i+2] = tree[l+2]
		tree[i+3] = tree[l+3]
		tree[i+4] = tree[l+4]
		tree[i+(mul*1)%5] += tree[r+1]
		tree[i+(mul*2)%5] += tree[r+2]
		tree[i+(mul*3)%5] += tree[r+3]
		tree[i+(mul*4)%5] += tree[r+4]
	}
}

func initleaf(o, value, k, stride int) {
	o *= stride
	clear(tree[o : o+stride])
	r := value % k
	tree[o+r] = 1
	tree[o+k] = uint32(r)
}

func build(n, k, stride int) {
	for i := n - 1; i > 0; i-- {
		merge((i<<1)*stride, (i<<1|1)*stride, i*stride, k)
	}
}

func update(index, value, n, k, stride int) {
	index += n
	initleaf(index, value, k, stride)
	for index >>= 1; index > 0; index >>= 1 {
		merge((index<<1)*stride, (index<<1|1)*stride, index*stride, k)
	}
}

func suffix(start, n, k, stride, x int) uint32 {
	l, r := start+n, 2*n
	left := 2 * n * stride
	right := left + stride
	next := right + stride
	hasleft, hasright := false, false

	for l < r {
		if l&1 != 0 {
			if !hasleft {
				for i := range stride {
					tree[left+i] = tree[l*stride+i]
				}
				hasleft = true
			} else {
				merge(left, l*stride, next, k)
				left, next = next, left
			}
			l++
		}
		if r&1 != 0 {
			r--
			if !hasright {
				for i := range stride {
					tree[right+i] = tree[r*stride+i]
				}
				hasright = true
			} else {
				merge(r*stride, right, next, k)
				right, next = next, right
			}
		}
		l >>= 1
		r >>= 1
	}

	if !hasleft {
		return tree[right+x]
	}
	if !hasright {
		return tree[left+x]
	}
	merge(left, right, next, k)
	return tree[next+x]
}

func castSlice[T1, T2 any](arr []T2) []T1 {
	return unsafe.Slice((*T1)(unsafe.Pointer(&arr[0])), len(arr))
}

func resultArray(nums []int, k int, queries [][]int) []int {
	n := len(nums)
	stride := k + 1

	for i, value := range nums {
		initleaf(n+i, value, k, stride)
	}
	build(n, k, stride)

	ans := castSlice[int](queries)
	for i, q := range queries {
		update(q[0], q[1], n, k, stride)
		ans[i] = int(suffix(q[2], n, k, stride, q[3]))
	}
	return ans
}