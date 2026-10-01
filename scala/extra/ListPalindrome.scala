import scala.io.StdIn

object ListPalindrome {

  def main(args: Array[String]): Unit = {

    print("Enter number of elements: ")
    val n = StdIn.readInt()
    var numbers = List[Int]()

    for (i <- 1 to n) {
      print("Enter element " + i + ": ")
      val num = StdIn.readInt()
      numbers = numbers :+ num
    }
    println("Original List: " + numbers)
    for(n<-numbers){
     var a=a+:
    }
    
   // if(numbers==numbers.reverse){
   // println("list is palindrome")}
   // else{
   // printf("list is not palindrome")}
   } 
  }

