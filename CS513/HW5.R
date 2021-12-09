#' Company : Stevens
#' Project : HW5
#' Purpose : HW5
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : October 25, 2021
#' 
#' 
#' ###### Homework 5 ####
#' 
rm(list=ls())
library(rpart)
library(rpart.plot)
library(rattle)
library(RColorBrewer) 
set.seed(513)
#'
#'
cancerData=read.csv("/Users/d0f05lt/Downloads/breast-cancer-wisconsin.csv", header=TRUE)
cancerData$F6 <- as.numeric(cancerData$F6)
cancerData <- cancerData[rowSums(is.na(cancerData)) == 0,]
cancerData <- na.omit(cancerData)
summary(cancerData)
idx<-sort(sample(nrow(cancerData),as.integer(.70*nrow(cancerData))))

training<-cancerData[idx,]

test<-cancerData[-idx,]

CART_class<-rpart( Class~.,data=training)
rpart.plot(CART_class)

CART_predict2<-predict(CART_class,test) 
table(Actual=test[,4],CART=CART_predict2)

CART_predict<-predict(CART_class,test)

table(Actual=test[,4],CART=CART_predict)
CART_wrong<-sum(test[,4]!=CART_predict)
CART_error_rate<-CART_wrong/length(test[,4])
CART_error_rate

library(rpart.plot)
prp(CART_class)

fancyRpartPlot(CART_class)

rm(list=ls())
