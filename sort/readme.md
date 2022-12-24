# Experiment of Sort Optimization
- result  
average of 50 times  

|||heap|||quick|||quick random|||quick middle 3|||quick mid expect||
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|n|comp|swap|time|comp|swap|time|comp|swap|time|comp|swap|time|comp|swap|time|
|100|668|580|29|420|420|19|390|457|21|530|416|21|399|450|22|
|200|1629|1357|45|938|938|27|958|1092|32|1191|964|29|914|1032|29|
|500|5082|4037|119|2834|2834|70|2870|3209|79|3350|2787|74|2614|2920|76|
|1000|11661|9074|206|6460|6460|122|6528|7204|133|7442|6313|136|5920|6564|132|
|2000|26330|20148|403|14359|14359|235|14311|15665|261|15949|13689|245|13155|14473|246|
|3000|42122|32077|548|22443|22443|331|22450|24483|340|24858|21462|342|20932|22926|339|
|4000|58719|44325|713|31069|31069|416|31506|34212|450|34065|29530|443|29169|31846|438|
|5000|75715|57125|916|39926|39926|538|40459|43843|572|43086|37422|560|37286|40628|564|
|10000|166371|124193|2076|87655|87655|1214|86385|93161|1291|94394|83093|1277|81296|88029|1255|
|20000|362728|268412|4564|188575|188575|2773|190850|204397|2900|198648|176057|2767|176089|189585|2710|

- n : size of array
- comp :  average comparison
- swap : average swap
- time : average time(ms)

creation of array : C random number between 0 and n


## Heap
Normal heap sort

## Quick
Normal quick sort
In the case of 50 repetitions, the operation time is shorter than the other quick sort algorithms.
It seems that the more the number of repetitions increases, the more the evenly mixed array increases.
Other quick sort algorithms were faster when the array is partially mixed or base pivot value was bad.

## Quick Random
Quick sort with randomly selected pivot values 

## Quick Middle 3
Method suggested by Robert Sedgewick.
Pivot value is median number among the first, the last, and the mid elements between low and high.
This method usually operated fewer swaps than the random selection method, and was slightly faster.

## Quick Mid Expect
In this special case, each element is uniformly distributed between 0 and n.
Therefore, the expected median number value for each partition function will be determined to some extent.
For example when n = 100, the median number in each partition function will be 50, 25, 75, 12.5, 27.5, ......
  
I came up with a method to choose a number which is as close as possible to the expected median as a pivot.
Since It would take too long if i compare too many numbers with expected median, I compared only 
log<sub>2</sub>(high-low) times in each partition function.

~~~
//pseudo code
midvalue is expected middle value between low and high
int current_difference = (array[pivot] - midvalue)
for(loop count log2(high-low)){
	tempidx = low + rand()%size;
	temp_difference = abs(array[tempidx] - midvalue);
	if(temp_difference < current_difference){
		current_difference = temp_difference;
		set tempidx as new pivot
	}
}
~~~
Since log2() function in <math.h> was slow, I transferred the log value as a function parameter and divided it by two.

## Result
When N is big enough, my "Quick Mid Expect Method" usually operated fewer comparison and fewer swaps than the "Quick Random Method", and was definitely faster.
When N is big enough, my "Quick Mid Expect Method" usually operated fewer comparison and more swap than the "Quick Middle 3 Method", and was slightly faster.
  
"Quick Mid Expect Method" seems good choice when each element is uniformly distributed.
