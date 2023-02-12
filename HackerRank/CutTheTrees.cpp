/*
푼 파일이 날라가서 재구현은 귀찮아서 그냥 접근법만 적어놓음.
사지방 브라우저가 문제인지는 모르겠으나 HackerRank 문제 Report 확인이 안된다...

처음에는 union find도 고민하고 bfs 접근도 고민했는데 둘다 O(N^2)로 시간초과
근데 dfs로 O(N)만에 풀 수 있음!
아무거나 하나 루트로 잡고 
(어떤 노드를 루트로 잡던 dfs 과정에서 생기는 subtree들은 동일하다. 
정확히는 subtree들이 동일하다기보다 생기는 subtree의 sum을 구하면 
나머지 subtree의 sum을 자동으로 알 수 있게 되는데,
어떤 노드를 루트로 잡던 만들어지는 하나의 subtree를 통해
나머지 하나의 subtree의 sum을 구할 수 있으므로
뭘 루트로 잡아도 상관이 없다. 이게 이 문제의 핵심이었다.)
DFS를 돌리며 각 노드들을 루트로 하는 subtree들의 sum을 구한다. (visited를 사용한다)
이후 구한 subtree들의 subtree sum들중 루트 sum(즉 모든 노드값합)의 1/2에 가장 근접한 값을 찾으면 
그 값을 이용해 나머지 subtree sum과의 차를 구할 수 있다.
*/
