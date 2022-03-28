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
class ANN(nn.Module) :
    def __init__(self):
        super(ANN,self).__init__()
        self.dense_1 = nn.Linear(in_features=784,out_features=256)
        self.dense_2 = nn.Linear(in_features=256,out_features=10)

        self.relu = nn.ReLU()
    def forward(self,x) :
        x = x.view(x.shape[0],-1)
        x = self.relu(self.dense_1(x))
        x = self.dense_2(x)
        # output = self.tanh(x)
        output = F.log_softmax(x, dim=1)

        return output

model = ANN()

summary(model, (1, 28, 28))

train(model,epochs=5)