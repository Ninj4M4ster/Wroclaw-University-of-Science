import tensorflow as tf
import numpy as np
from tensorflow import keras
import os
import matplotlib.pyplot as plt


def create_model():
    model = keras.models.Sequential([
        keras.layers.Flatten(input_shape=(28, 28)),
        keras.layers.Dense(128, activation="relu", kernel_regularizer=keras.regularizers.l2(0.0001)),
        keras.layers.Dropout(0.5),
        keras.layers.Dense(10)
    ])

    model.compile(optimizer='adam',
                  loss=tf.losses.SparseCategoricalCrossentropy(from_logits=True),
                  metrics=['accuracy'])

    return model


def train_model(model, train_images, train_labels, test_images, test_labels, weights_file_name):
    checkpoint_path = "minst_model/" + weights_file_name

    callback = keras.callbacks.ModelCheckpoint(filepath=checkpoint_path,
                                               save_weights_only=True,
                                               verbose=1)

    model.fit(train_images,
              train_labels,
              epochs=10,
              validation_data=(test_images, test_labels),
              callbacks=[callback])


def load_weights(model, weights_file_name):
    checkpoint_path = "minst_model/" + weights_file_name
    model.load_weights(checkpoint_path)


def main():
    digits = keras.datasets.mnist
    (train_digits, train_labels), (test_digits, test_labels) = digits.load_data()
    model = create_model()
    # load_weights(model, "minst_model.ckpt")

    train_digits = train_digits / 255.0
    test_digits = test_digits / 255.0

    train_model(model, train_digits, train_labels, test_digits, test_labels, "minst_model.ckpt")

    loss, acc = model.evaluate(test_digits, test_labels)
    print(f"Accuracy: {acc * 100:5.2f}")


if __name__ == '__main__':
    main()
