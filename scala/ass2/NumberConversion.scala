import scala.io.StdIn

object NumberConversion {

  def toBinary(num: Int): String = {
    Integer.toBinaryString(num)
  }

  def toOctal(num: Int): String = {
    Integer.toOctalString(num)
  }

  def main(args: Array[String]): Unit = {

    print("Enter an integer: ")
    val num = StdIn.readInt()

    println(s"Binary: ${toBinary(num)}")
    println(s"Octal: ${toOctal(num)}")
  }
}
