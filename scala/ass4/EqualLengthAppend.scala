import scala.io.StdIn

object EqualLengthAppend {
  def main(args: Array[String]): Unit = {

    println("Enter first string:")
    var str1 = StdIn.readLine()

    println("Enter second string:")
    var str2 = StdIn.readLine()

    
    if (str1.length > str2.length) {

     
      str1 = str1.drop(str1.length - str2.length)

    } else if (str2.length > str1.length) {

      
      str2 = str2.drop(str2.length - str1.length)
    }

  
    var result = str1 + str2

    println("First String = " + str1)
    println("Second String = " + str2)
    println("Result = " + result)
  }
}
