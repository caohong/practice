from django.conf.urls import include, url
from django.contrib import admin
import video_store.urls

urlpatterns = [
    url(r'^admin/', include(admin.site.urls)),
    url(r'^video/', include('video_store.urls'), name='video')
]