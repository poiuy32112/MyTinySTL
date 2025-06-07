#include <iostream>
#include <vector>

void print(std::vector<int>& nums) {
	for (int i : nums) {
		std::cout << i << " ";
	}
	std::cout << '\n';
}

//—°‘Ò≈≈–Ú
void selection_sort(std::vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n - 1; ++i) {
		int k{ i };
		for (int j = i + 1; j < n; ++j) {
			if (nums[j] < nums[k]) {
				k = j;
			}
		}
		std::swap(nums[i], nums[k]);
	}
}

//√∞≈›≈≈–Ú
void bubble_sort(std::vector<int>& nums) {
	int n = nums.size();
	for (int i = n - 1; i > 0; --i) {
		int j = 0;
		while (j < i) {
			if (nums[j] > nums[j + 1]) {
				std::swap(nums[j], nums[j + 1]);
			}
			j++;
		}
	}
}

//≤Â»Î≈≈–Ú
void insertion_sort(std::vector<int>& nums) {
	int n = nums.size();
	for (int i = 1; i < n; ++i) {
		int j = i - 1;
		int num = nums[i];
		while (j >= 0 && nums[j] > num) {
			nums[j + 1] = nums[j];
			j--;
		}
		nums[j + 1] = num;
	}
}

//øÏÀŸ≈≈–Ú
int partition(std::vector<int>& nums, int left, int right) {
	int l = left;
	int r = right;
	while (l < r) {
		while (l < r && nums[r] >= nums[left]) r--;
		while (l < r && nums[l] <= nums[left]) l++;
		std::swap(nums[l], nums[r]);
	}
	std::swap(nums[l], nums[left]);
	return l;
}

void quick_sort(std::vector<int>& nums, int left, int right) {
	if (left >= right) return;
	int pivot = partition(nums, left, right);
	quick_sort(nums, left, pivot - 1);
	quick_sort(nums, pivot + 1, right);
}

//∂—≈≈–Ú
void shift_down(std::vector<int>& nums, int i, int n) {
	while (true) {
		int l = i * 2 + 1;
		int r = i * 2 + 2;
		int ma = i;
		if (l < n && nums[l] > nums[ma]) ma = l;
		if (r < n && nums[r] > nums[ma]) ma = r;
		if (i == ma) return;
		std::swap(nums[i], nums[ma]);
		i = ma;
	}
}

void heap_sort(std::vector<int>& nums) {
	int n = nums.size();
	for (int i = n / 2 - 1; i >= 0; --i) {
		shift_down(nums, i, n);
	}

	for (int len = n; len > 0; --len) {
		std::swap(nums[0], nums[len - 1]);
		shift_down(nums, 0, len - 1);
	}
}

//πÈ≤¢≈≈–Ú
void merge(std::vector<int>& nums, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = 0;
	std::vector<int> tmp(right - left + 1);
	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {
			tmp[k++] = nums[i++];
		} else {
			tmp[k++] = nums[j++];
		}
	}
	while (i <= mid) {
		tmp[k++] = nums[i++];
	}
	while (j <= right) {
		tmp[k++] = nums[j++];
	}
	for (int k = 0; k < tmp.size(); ++k) {
		nums[left + k] = tmp[k];
	}
}

void merge_sort(std::vector<int>& nums, int left, int right) {
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	merge_sort(nums, left, mid);
	merge_sort(nums, mid + 1, right);
	merge(nums, left, mid, right);
}

//ª˘ ˝≈≈–Ú
void gewei(std::vector<int>& nums, int exp) {
	int n = nums.size();
	std::vector<int> tmp(n);
	int buckets[10]{ 0 };
	for (int i = 0; i < n; ++i) {
		buckets[nums[i] / exp % 10]++;
	}
	for (int i = 1; i < 10; ++i) {
		buckets[i] += buckets[i - 1];
	}
	for (int i = n - 1; i >= 0; --i) {
		tmp[buckets[nums[i] / exp % 10] - 1] = nums[i];
		buckets[nums[i] / exp % 10]--;
	}
	nums = tmp;
}

void jishu_sort(std::vector<int>& nums) {
	int n = nums.size();
	int max_num = *max_element(nums.begin(), nums.end());
	for (int exp = 1; max_num / exp > 0; exp *= 10) {
		gewei(nums, exp);
	}
}

//œ£∂˚≈≈–Ú
void shell_sort(std::vector<int>& nums) {
	int n = nums.size();
	for (int d = n / 2; d >= 1; d = d / 2) {
		for (int i = d; i < n; ++i) {
			if (nums[i] < nums[i - d]) {
				int j = i - d;
				int num = nums[i];
				for (; j >= 0 && num < nums[j]; j -= d) {
					nums[j + d] = nums[j];
				}
				nums[j + d] = num;
			}
		}
	}
}


int main() {
	std::cout << "—°‘Ò≈≈–Ú£∫\n";
	std::vector<int> vec{ 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	selection_sort(vec);
	print(vec);

	std::cout << "œ£∂˚≈≈–Ú£∫\n";
	//vec = { 2, 1, 4, 3};
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	shell_sort(vec);
	print(vec);

	std::cout << "ª˘ ˝≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, 1, 3, 4, 35, 36 };
	//vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	jishu_sort(vec);
	print(vec);

	std::cout << "πÈ≤¢≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	merge_sort(vec, 0, vec.size() - 1);
	print(vec);

	std::cout << "∂—≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	heap_sort(vec);
	print(vec);

	std::cout << "√∞≈›≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	bubble_sort(vec);
	print(vec);

	std::cout << "≤Â»Î≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	insertion_sort(vec);
	print(vec);

	std::cout << "øÏÀŸ≈≈–Ú£∫\n";
	vec = { 0, 6, 10, 4, 35, -1,-23, 1, 3, 4, -1, 35, 36 };
	quick_sort(vec, 0, vec.size() - 1);
	print(vec);
	return 0;
}