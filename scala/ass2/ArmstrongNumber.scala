import scala.io.StdIn

object ArmstrongNumber {

  def isArmstrong(num: Int): Boolean = {

    var n = num
    var digits = 0

    while (n > 0) {
      digits += 1
      n /= 10
    }

    n = num
    var sum = 0

    while (n > 0) {
      val digit = n % 10
      sum += math.pow(digit, digits).toInt
      n /= 10
    }

    sum == num
  }

  def main(args: Array[String]): Unit = {

    print("Enter an integer: ")
    val num = StdIn.readInt()

    if (isArmstrong(num))
      println(s"$num is an Armstrong number")
    else
      println(s"$num is not an Armstrong number")
  }
}
