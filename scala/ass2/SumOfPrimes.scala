object SumOfPrimes {

  def isPrime(num: Int): Boolean = {
    if (num < 2)
      false
    else {
      var flag = true

      for (i <- 2 until num if num % i == 0) {
        flag = false
      }

      flag
    }
  }

  def main(args: Array[String]): Unit = {

    var sum = 0

    for (i <- 1 to 100 if isPrime(i)) {
      sum += i
    }

    println(s"Sum of prime numbers between 1 and 100 = $sum")
  }
}
