#  Course          :  
#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         :  

## Step 0 clean up!!!


rm(list=ls())

file<-file.choose()
dsn<- read.csv(file)

#install.packages('randomForest')
dev.off()

library(randomForest)
 
?randomForest()
?importance()
?tuneRF()
file<-file.choose()
dsn<- read.csv(file )


?read.csv()
set.seed(123)
dsn2<-na.omit(dsn)
set.seed(111)
?ifelse


index<-sort(sample(nrow(dsn2),round(.30*nrow(dsn2))))
training<-dsn[-index,]
test<-dsn[index,]
#install.packages('randomForest')
library(randomForest)
fit <- randomForest( Survived~., data=training, importance=TRUE, ntree=1000)
importance(fit)
varImpPlot(fit)
Prediction <- predict(fit, test)
table(actual=test[,4],Prediction)


wrong<- (test[,4]!=Prediction )
error_rate<-sum(wrong)/length(wrong)
error_rate 

 
