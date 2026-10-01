object array{
  def main(args:Array[String]):Unit={
       var a:Array[Int]= Array(-10,0,30,-40)
       
       for(n<- a){
       if(n>0)
       println(s" $n positive")
       else if(n<0)
       println(s" $n negative")
       else println(s" $n zero")    
       }
       }
}
