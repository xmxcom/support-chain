
#ifdef USE_V8
#include "jsvm_util.h"
#include <iostream>
#include "jsvm_objbind/Int64Bind.h"
namespace Xmaxplatform {

	namespace Chain {

		void EnterJsContext(Isolate* pIsolate,DoWorkInJsCtx dowork)
		{
			HandleScope current_handle_scope(pIsolate);

			v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(pIsolate);

			BindJsFoos(pIsolate, global, FooBind::GetBindFoos(pIsolate));
			SetupV8i64ObjectToJs(pIsolate, global);
			Local<Context> context = Context::New(pIsolate, NULL, global);
			Context::Scope context_scope(context);

			dowork(current_handle_scope, global, context, context_scope);
		}


		void BindJsFoos(Isolate* pIsolate,const Local<ObjectTemplate>& fooGlobal,const std::map<std::string, Local<FunctionTemplate>>& foosToBind)
		{
			for (const std::pair<std::string, Local<FunctionTemplate> >& foobind : foosToBind)
			{
				fooGlobal->Set(
					v8::String::NewFromUtf8(pIsolate, foobind.first.c_str(), v8::NewStringType::kNormal).ToLocalChecked(),
					foobind.second);
			}
		}

		void CompileJsCode(Isolate* pIsolate,const Local<Context>& context, char* jsCode)
		{
			Local<String> source =
				String::NewFromUtf8(pIsolate, jsCode,
					NewStringType::kNormal).ToLocalChecked();
			MaybeLocal<Script> temp = Script::Compile(context, source);

			if (temp.IsEmpty())
			{
				std::cerr << "js compile failed" << std::endl;
			}
			Local<Script> script = temp.ToLocalChecked();
			if (script.IsEmpty()) {
				std::cerr << "js compile failed" << std::endl;
			}

			script->Run();
		}

		v8::Handle<v8::Value> CallJsFoo(Isolate* pIsolate, const Local<Context>& context,const char* fooname, unsigned int argc,Handle<v8::Value>* params)
		{
			Handle<String> js_func_name = String::NewFromUtf8(pIsolate, fooname, NewStringType::kNormal).ToLocalChecked();
			Handle<v8::Value>  js_func_val = context->Global()->Get(js_func_name);
			if (!js_func_val->IsFunction())
			{
				std::cerr << "Can't find js funcion init()" << std::endl;
				return  Undefined(pIsolate);
			}
			else
			{
				Handle<Function> js_func = Handle<Function>::Cast(js_func_val);
				Handle<v8::Value> hResult = js_func->Call(context->Global(), argc, params);
				return hResult;
			}
		}

		Handle<v8::Value> I64Cpp2JS(Isolate* isolate, const Local<Context>& context, int64_t v)
		{
			Handle<String> js_data = String::NewFromUtf8(isolate, "V8i64", NewStringType::kNormal).ToLocalChecked();
			Handle<v8::Value> js_data_value = context->Global()->Get(js_data);

			bool bIsObject = js_data_value->IsObject();
			if (bIsObject)
			{
				Handle<Object> js_data_object = Handle<Object>::Cast(js_data_value);

				int* pvarr = (int*)&v;

				Handle<v8::Value>  argcodev[2];
				argcodev[0] = Int32::New(isolate, pvarr[1]);
				argcodev[1] = Int32::New(isolate, pvarr[0]);

				Handle<v8::Value> codeObj = js_data_object->CallAsConstructor(2, argcodev);
				return codeObj;
			}
			return Undefined(isolate);
		}
		/*
		int64_t  I64JS2Cpp(Isolate* isolate,Handle<Object> jsobj)
		{
			Handle<Object> js_data_object = Handle<Object>::Cast(js_data_value);

			Handle<String> js_func_name = String::NewFromUtf8(
				Xmaxplatform::Chain::jsvm_xmax::get().current_state->current_isolate,
				"toOctetString",
				NewStringType::kNormal).ToLocalChecked();
		}*/

		namespace FooBind
		{
			void FooBind::exportFoo(const FunctionCallbackInfo<v8::Value>& args)
			{
				bool first = true;
				for (int i = 0; i < args.Length(); i++) {
					v8::HandleScope handle_scope(args.GetIsolate());
					//args[i]
					Handle<v8::Value> js_data_value = args[i];

					bool bIsObject = js_data_value->IsObject();
					if (bIsObject)
					{
						/*
						Handle<Object> js_data_object = Handle<Object>::Cast(js_data_value);

						Handle<String> js_func_name = String::NewFromUtf8(
							Xmaxplatform::Chain::jsvm_xmax::get().current_state->current_isolate,
							"toOctetString",
							NewStringType::kNormal).ToLocalChecked();

						Handle<String> js_param_name = String::NewFromUtf8(
							Xmaxplatform::Chain::jsvm_xmax::get().current_state->current_isolate,
							" ",
							NewStringType::kNormal).ToLocalChecked();

						Handle<Value>  js_func_ref = js_data_object->Get(js_func_name);
						Handle<Function> js_func = Handle<Function>::Cast(js_func_ref);

						Handle<v8::Value> args[1];
						args[0] = js_param_name;

						Handle<Value> result = js_func->Call(js_data_object, 1, args);

						String::Utf8Value utf8(result);
						printf("%s\n", *utf8);
						*/
					}
				}
			}
		}



	}
}
#endif