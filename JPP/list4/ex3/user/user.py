from typing import Type, TypeVar, Generic, List
import random
from body.gf import Gf1234577
from dh_setup.dh_setup import DHSetup
import copy

T = TypeVar('T', bound=Gf1234577)

class User(Generic[T]):
    _dh_setup: DHSetup[T]
    _t_class: T

    _encrypting_key: T
    _key_set = False
    _secret: int

    def __init__(self, dh_setup: DHSetup[T], t_class: Type[T]) -> None:
        self._dh_setup = dh_setup
        self._t_class = t_class
        self._secret = random.randint(1, self._t_class.Characteristic() - 1)

    def getPublicKey(self):
        return self._dh_setup.power(self._dh_setup.getGenerator(), self._secret)
    
    def setKey(self, a: T):
        self._encrypting_key = self._dh_setup.power(a, self._secret)
        self._key_set = True

    def encrypt(self, m: T):
        if not self._key_set:
            raise Exception("No key was set, data cannot be encrypted")
        return m * self._encrypting_key
    
    def decrypt(self, c: T):
        if not self._key_set:
            raise Exception("No key was set, data cannot be decrypted")
        return c / self._encrypting_key