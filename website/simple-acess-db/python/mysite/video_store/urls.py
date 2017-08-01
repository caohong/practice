from django.conf.urls import url
from . import views

urlpatterns = [
    # url(r'^/', views.index, name='index'),
    url(r'^$', views.index, name='index'),
    url(r'getUrl/(?P<vid>[0-9]+)', views.getUrl, name='getUrl')
]