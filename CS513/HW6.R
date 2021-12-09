#' Company : Stevens
#' Project : HW6
#' Purpose : HW6
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : November 15, 2021
#' 
#' 
#' ###### Homework 6 ####
#' 
rm(list=ls())
library('C50')
library(randomForest)
set.seed(513)
#'
#'
#' Data pre-processing
#'
cancerData=read.csv("/Users/davidfu/Downloads/breast-cancer-wisconsin.csv", header=TRUE)
cancerData$Class <- as.factor(cancerData$Class)


index<-sort(sample(nrow(cancerData),round(.30*nrow(cancerData))))
training<-cancerData[-index,]
test<-cancerData[index,]

#' 6.1
#'
C50_class <- C5.0( Class~.,data=training )

summary(C50_class)
plot(C50_class)
C50_predict<-predict( C50_class ,test , type="class" )
table(actual=test[,4],C50=C50_predict)
wrong<- (test[,4]!=C50_predict)
c50_rate<-sum(wrong)/length(test[,4])
c50_rate

#' 6.2
#'

fit <- randomForest( Class~., data=training, importance=TRUE, ntree=1000)
importance(fit)
varImpPlot(fit)
Prediction <- predict(fit, test)
table(actual=test[,4],Prediction)


wrong<- (test[,4]!=Prediction )
error_rate<-sum(wrong)/length(wrong)
error_rate 

#' Memory Clean up
rm(list=ls())

