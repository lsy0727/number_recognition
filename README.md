# number_recognition

필기체 숫자 입력, 저장, 불러오기, 인식, 삭제, 종료 기능을 하는 UI를 구현함

1. 메인함수
   1) UI그리기 함수 호출
   2) 마우스 이벤트 함수 호출

2. UI그리기 함수
   1) 칸 나누기 : line()함수로 선을 그려 칸을 나누고, 테두리는 rectangle()함수를 이용해 그린다.
   2) 글씨 넣기
   3) UI가 그려진 영상 복사

   Rect(0,0,500,500)영역은 입력창 영역이기 때문에 x좌표에 500을 더함

   ![image](https://github.com/lsy0727/number_recognition/assets/92630416/45b1483c-e582-4716-a559-338059854efd)

3. 마우스 이벤트 함수

   contains() 함수는 영역 내에 점이 존재하는지 구분하기 위해 사용하고, 존재하면 ture, 존재하지 않으면 false를 반환한다.
   
   1) save : 파일명을 입력받고 imwrite()함수를 이용해 저장한다.
   2) load : 파일명을 입력받고 imread()함수를 이용해 불러옴, 바로 화면에 나타나지 않기때문에 imshow()함수 사용한다.
   3) clear : UI그리기 함수에서 복사해둔 영상을 다시 복사한다.
   4) run(미구현) : 입력창에서 그린 숫자가 몇인지 구별하고 콘솔창에 출력한다.
   5) exit : 콘솔창에 "프로그램 종료"메시지를 출력한 후 종료한다.
   6) 입력창 영역 내에서 마우스 왼쪽버튼을 누른상태로 드래그시 선이 그려진다.

https://github.com/lsy0727/number_recognition/assets/92630416/7616b1ca-b34b-49e4-a992-8082c3fa8f31

