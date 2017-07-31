from django.conf.urls import include, url
from django.contrib import admin
import video_store.urls

urlpatterns = [
    # Examples:
    # url(r'^$', 'mysite.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    # url(r'^video/', include('video_store.urls'), name='video_store')
    url(r'^video/', video_store.views.index, name='index')
]
