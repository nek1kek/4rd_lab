import time
import matplotlib.pyplot as plt

f = open('for_graphics_on_python.txt', 'r')  # открыть файл из рабочей директории в режиме чтения
arr_x = list(map(int, f.readline().split('\t')[:-1]))
arr_y = list(map(float, f.readline().split('\t')[:-1]))

SortType = dict(enumerate(['ShakerSort', 'BinaryInsertionSort', 'MergeSort', 'QuickSort', 'BitonicSort']))
type_of_sort = SortType[int(f.readline())]
f.close()

name_of_graphics = type_of_sort + ' by p4vel'  # there is will be name of group
fig, ax = plt.subplots()
ax.plot(
    arr_x,
    arr_y,
    "bo-",
    linewidth=2,
    markersize=10,
)  # get graphic
ax.set_ylabel("Время в микросекундах")
ax.set_xlabel("Кол-во элементов")

for i in range(len(arr_x)):
    x = arr_x[i]
    y = arr_y[i]
    plt.text(
        x + 500,
        y - 0.1*y,
        str(arr_y[i]) + 'мкс',
        fontsize=8,
    )

ax.set_title(name_of_graphics)
plt.show()
plt.clf()  # we must clear plt!
