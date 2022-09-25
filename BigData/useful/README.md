# Things Useful to Know

> ### references 🔗
> [Mining of Massive Datasets](http://www.mmds.org/#book)

Data Mining을 공부하는 데 도움이 되는 개념들이다.

## Contents		
* ### [What is Data Mining?](#)
* ### [TF.IDF](#)      
* ### [Hash Functions](#)      
* ### [Secondary storage and its effect](#)

#    

## What is Data Mining?
가장 강력한 하드웨어, 가장 강력한 프로그래밍 시스템과 가장 효율적인 알고리즘을 사용하여 사람의 노력이 필요한 다양한

분야(상업, 의료 등)의 문제를 해결하는 것이 data mining의 본질적인 목표이다.

## Important Words in documents
임의의 document의 주제를 파악하는(또는 카테고리를 결정하는) 일은 그 문서의 중요한 단어들을 찾는 것으로 시작된다.

사실, 분류를 시작하기 전, 영어(또는 한국어)에서 가장 자주 사용되는 단어(stop words)들은 제거된다. 이런 어휘에는 a, the 등의 관사가 포함된다.

실제로 글의 주제와 관련된 단어들은 보기 드문 단어들이다. 하지만, 보기 드문 모든 단어가 주제를 알려주는 indicator가 되는 것은 아니다.

그냥 보기 드문 단어와 indicator가 될 수 있는 희귀한 단어의 차이는 재등장 여부이다. indicator는 한 번 등장했다면 다시 등장할 확률이 높다.

**TF.IDF**(Term Frequency * Inverse Document Frequency)는 주어진 단어가 **얼마나 적은 수의 문서들에서 얼마나 집중되어 등장하는 지를 표현**하는 값이다.
> 직역하면 (단어 횟수)/(문서 횟수) 이다.

쉽게 말하면 **TF.IDF 값이 높을수록 해당 단어는 그 문서의 주제를 표현하는 단어일 가능성이 높다.**

### TF(Term Frequency)
> 하나의 문서에서 자주 등장하면 커지는 값

N개의 문서에 대해 단어 𝑖가 문서 𝑗에서 등장한 횟수를 f𝑖𝑗라고 하면, term frequency는 다음과 같다.
<img src="./img/tf.png" width="70%" alt="TF">

max𝑘f𝑘𝑗는 문서𝑗에서 가장 많이 등장한 단어의 등장 횟수이다. 

**가장 자주 등장한 단어의 TF값은 1이다.**

### IDF(Inverse Document Frequency)
> 여러 문서들에서 자주 등장할수록 값이 작아진다.

term 𝑖가 N개의 문서에서 등장한 횟수를 n𝑖이라고 하면
<img src="./img/idf.png" width="70%" alt="IDF">

## Hash Function
Hash function 𝒉는 key를 입력으로 받아 **bucket number**를 출력한다.

* hash key : 어떤 type이든 될 수 있다.
* bucket number : 0 ~ B-1 까지의 값을 가지는 정수. (B는 bucket의 개수)

잘 만들어진 hash function은 임의의 hash key들을 B개의 bucket에 **거의 비슷한 수로 보낸다.**

## Index
index는 임의의 object의 하나 이상의 field 값이 주어졌을 때 해당 object를 빠르게 찾도록 도와준다.

가장 일반적인 예시는 object가 record이고 index는 record의 field(attribute)인 경우이다. 

예를 들어 하나의 파일에 (name, address, phone number)라는 record들이 저장되어 있고 phone number가 index라고 하자.

phone number 값이 𝒗로 주어지면 모든 record들의 phone number 값들과 𝒗값을 비교할 필요 없이 바로 phone number가 𝒗인 record를 찾을 수 있다.

이런 index는 hash function을 사용해 구현할 수 있다.

index인 필드가 hash key가 되고 해당 record가 대응되는 bucket에 담겨있다.

hash key가 주어지면 그에 대응되는 bucket에서만 record를 탐색하면 된다. 그러므로 임의의 record를 찾는데 걸리는 시간을 O(R/B)로 표현할 수 있다.

> R은 record의 수, B는 bucket의 수
