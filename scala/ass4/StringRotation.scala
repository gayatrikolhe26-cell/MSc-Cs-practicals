import scala.io.StdIn

object StringRotation {
  def main(args: Array[String]): Unit = {

    println("Enter first string:")
    var str1 = StdIn.readLine()

    println("Enter second string:")
    var str2 = StdIn.readLine()

    
    if (str1.length == str2.length) {

      
      var combined = str1 + str1

 
      if (combined.contains(str2)) {
        println("The strings are rotations of each other.")
      } else {
        println("The strings are not rotations of each other.")
      }

    } else {
      println("The strings are not rotations of each other.")
    }
  }
}
