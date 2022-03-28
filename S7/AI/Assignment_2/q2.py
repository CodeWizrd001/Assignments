import torch
import torchvision
from torch import nn, optim

import torch.nn.functional as F
from torchsummary import summary

# Model Configs
batch_size = 64
learning_rate = 0.01
cross_entropy = nn.CrossEntropyLoss()

# Data Loader
transform = torchvision.transforms.ToTensor()
train_data = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(
    'mnist_data', train=True, download=True, transform=transform
    ), batch_size=batch_size
)
val_data = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(
    'mnist_data', train=False, download=True, transform=transform
    ), batch_size=batch_size
)

# Validation function
def validate(model, data):
    total = 0
    correct = 0
    for i, (images, labels) in enumerate(data):
        images = images
        labels = labels
        y_pred = model(images)
        value, pred = torch.max(y_pred, 1)
        total += y_pred.size(0)
        correct += torch.sum(pred == labels)
    return correct * 100 / total

# Training Function
def train(model,epochs=5) :
    optimizer = optim.Adam(model.parameters(),lr=learning_rate)    
    for n in range(epochs)  :
        for i , (images , labels) in enumerate(train_data) :
            images = images
            labels = labels
            optimizer.zero_grad()
            prediction = model(images)
            loss = cross_entropy(prediction, labels)
            loss.backward()
            optimizer.step()
        accuracy = float(validate(model, val_data))
        print("Epoch:", n+1, "Loss: ", float(loss.data), "Accuracy:", accuracy)

# Model
class CNNWithPool(nn.Module) :
    def __init__(self):
        super(CNNWithPool,self).__init__()
        self.conv_1 = nn.Conv2d(in_channels=1,out_channels=16,kernel_size=3)
        self.conv_2 = nn.Conv2d(in_channels=16,out_channels=32,kernel_size=3)
        
        self.pool_1 = nn.MaxPool2d(2)
        self.pool_2 = nn.MaxPool2d(2)

        self.dense_1 = nn.Linear(in_features=800,out_features=256)
        self.dense_2 = nn.Linear(in_features=256,out_features=10)

        self.tanh = nn.Tanh()
    def forward(self,x) :
        x = self.tanh(self.conv_1(x))
        x = self.pool_1(x)
        x = self.tanh(self.conv_2(x))
        x = self.pool_2(x)
        x = x.view(x.shape[0],-1)
        x = self.tanh(self.dense_1(x))
        x = self.dense_2(x)
        # output = self.tanh(x)
        output = F.log_softmax(x, dim=1)

        return output

model = CNNWithPool()

summary(model, (1, 28, 28))

train(model,epochs=5)