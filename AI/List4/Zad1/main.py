import tensorflow_decision_forests as tfdf
import tensorflow_datasets as tfds
import tensorflow as tf
import pandas as pd
import numpy as np


def main():
    (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
    x_train = x_train / 255.0
    x_test = x_test / 255.0
    x_train2 = x_train.reshape((60000, 28 * 28))

    model = tfdf.keras.RandomForestModel(verbose=0)
    model.fit(x_train2, y_train)

    x_test2 = x_test.reshape((10000, 28*28))

    model.compile(metrics=["accuracy"])
    print(model.evaluate(x_test2, y_test))


if __name__ == '__main__':
    main()
