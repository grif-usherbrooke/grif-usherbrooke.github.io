
arr = [1,2,3,4]


for (var i = 0; i < 10; i++)
{
	arr[i % arr.length] = arr[(i) % arr.length] + arr[(i * i) % arr.length]
}

