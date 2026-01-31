//#include<iostream>
//#include<stack>
//
//using namespace std;
//
//class MinStack {
//public:
//    MinStack() {}
//
//    void push(int val) {
//        _st.push(val);
//        if (_minst.empty() == true || _minst.top() >= val)
//            _minst.push(val);
//    }
//
//    void pop() {
//        if (_st.top() == _minst.top())
//            _minst.pop();
//        _st.pop();
//    }
//
//    int top() { return _st.top(); }
//
//    int getMin() { return _minst.top(); }
//    stack<int> _st;
//    stack<int> _minst;
//};
//
//
//int main()
//{
//    MinStack s;
//
//    s.push(46);
//    s.push(46);
//    s.push(47);
//    s.top();
//    s.pop();
//    cout<<s.getMin();
//    s.pop();
//   cout<< s.getMin();
//    s.pop();
//    s.push(47);
//    s.top();
//   cout<< s.getMin();
//
//    s.push(-48);
//    s.top();
//    s.getMin();
//    s.pop();
//    s.getMin();
//
//
//   
//	return 0;
//}